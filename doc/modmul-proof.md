Proof for why the following:

```cpp
typedef uint64_t u64;
typedef int64_t i64;
typedef long double ld;

u64 modmul(u64 a, u64 b, u64 c) {
    i64 ret = a * b - c * u64(ld(a) * ld(b) / ld(c));
    return ret + c * (ret < 0) - c * (ret >= (i64)c);
}
```

correctly computes `a * b % c` for all 0 ≤ a, b < c < 2^63.

---


The algorithm consists of two parts: first approximately reducing `a * b % c`, into `[-c, 2c)`,
then reducing that further into `[0, c)`. Note the algorithm only ever adds/subtracts multiplies
of `c`, so it is clear that the end result is congruent to `ab (mod c)`. The main difficulties
in proving it correct lie in showing that the floating point calculation reduces it into
the right interval, and then separately in showing that using limited-precision integers is fine.
We start with the first point.


Let `round(x)` denote rounding `x` to the nearest long double, and `frac(x) = x - floor(x)`.
Note that long doubles are 80-bit floats, with 1+63-bit mantissa (the first bit always being 1).
They can thus represent all integers in `[0, 2^64]`, but not `2^64 + 1`.
Multiplication and division are both precise to within 0.5 ulp -- they round to the float
nearest to their mathematically exact result, and in case of ties, to the float with a trailing zero bit.


We shall start by proving that the integer `a * b - c * u64(ld(a) * ld(b) / ld(c))` lies within the range `[-c, 2c)`.

Because of how rounding works, we have for each positive x (in our exponent range) that `|round(x) - x| ≤ x * 2^-64`.
Thus we can write each `round(x)` as `x * (1 + ε/2^-64)` where `|ε| ≤ 1`.
Also, let us write `floor(x)` as `x - ε` with `0 ≤ ε < 1`.

Then we can incrementally rewrite/strengthen the inequality:

`ab - floor(round(round(ab) / c))*c ∈ [-c, 2c)`

`floor(round(round(ab) / c)) ∈ ab/c + (-2, 1]`

`round(round(ab) / c) - ε ∈ ab/c + (-2, 1]`

⇐ `round(round(ab) / c) ∈ ab/c + [-1, 1]`

`ab / c (1+ε₁/2^-64)(1+ε₂/2^-64) ∈ ab/c + [-1, 1]`

`ab / c (ε₁/2^-64 + ε₂/2^-64 + ε₁ε₂/2^-128) ∈ [-1, 1]`

`ab / c |ε₁/2^-64 + ε₂/2^-64 + ε₁ε₂/2^-128| ≤ 1`

⇐ `ab / c (2/2^-64 + 1/2^-128) ≤ 1`

`ab / c ≤ 1 / (1/2^-63 + 1/2^-128)`

⇐ `(c-1)(c-1)/c ≤ 1 / (1/2^-63 + 1/2^-128)`

`c - 2 + 1/c ≤ 1 / (1/2^-63 + 1/2^-128)`

`c - 1 ≤ 1 / (1/2^-63 + 1/2^-128)`

`c - 1 ≤ 2^63 * (1 - 2^-65 / (1 + 2^-65))`

⇐ `c - 1 ≤ 2^63 * (1 - 2^-65)`

`c - 1 ≤ 2^63 - 2^-2`

which holds for `c ≤ 2^63`.


Given the above, the algorithm works if we treat `ret` as an arbitrary-precision integer.
However, it is not. The computation of `ret`, apart from the floating-point steps, will be
performed with 64-bit unsigned integers, and then converted to a 64-bit signed integer.
This corresponds to performing arithmetic modulo 2^64, and then taking representatives
in `[-2^63, 2^63)`. If we can show that the range we reduce the result into fits in
`[-2^63, 2^63)`, then the modular arithmetic does not destroy anything, and the algorithm
works as expected.

If `c ≤ 2^62`, `[-c, 2c)` does fit entirely within that range, and so the algorithm works.
The interesting case happens when `2^62 < c < 2^63`. The range `[-c, c)` still fits within
i64; however, `[c, 2*c)` does not -- `2*c` overflows. We shall prove, however, that
the approximation in fact never returns a value greater than or equal to 2^63, and so
the algorithm works even for `c` in this larger range. (It would actually work for `c = 2^63`
as well, if it weren't for the fact that "(i64)c" then overflows.)


What we will prove is that `ab - floor(round(round(ab) / c))*c < 2^63` always holds.
Let's assume the opposite for sake of contradiction.

If `round(ab) / c ≥ ab / c` we're fine:
`floor(round(round(ab) / c)) ≥ floor(round(ab / c)) ≥ floor(ab / c)`, since floor and round
are monotonic, and since `ab / c < c^2/c ≤ 2^63` the integer `floor(ab / c)` is
representable, so `round` can't skip past it. Thus,
`ab - floor(round(round(ab) / c))*c ≤ ab - floor(ab / c)*c = ab % c < c ≤ 2^63`, contradiction.

Otherwise, `round(ab) / c < ab / c < c^2/c ≤ 2^63`.
Let k be such that `2^k ≤ round(ab) / c < 2^(k+1)`; then `k ≤ 62`.

If `round(round(ab) / c)` rounds upward to an integer, then
`ab - floor(round(round(ab) / c))*c =
ab - round(round(ab) / c)*c ≤
ab - round(ab) / c * c =
ab - round(ab) ≤
ab * 2^-64 < c^2/2^64 < 2^63`, contradiction.

Otherwise, since `round(round(ab) / c)` only has 64 bits of precision and `round`
rounds to nearest, breaking ties towards even, `frac(round(ab) / c) < 1 - 2^(k-64)`.
(This is the magic part.)

Division can't move us below an integer, so `floor(round(round(ab) / c)) = floor(round(ab) / c)`.
Thus we can rewrite our inequality as

`ab - floor(round(ab) / c)*c ≥ 6^63`

⇔ `ab - ((round(ab) / c) - frac(round(ab) / c))*c ≥ 6^63`

⇔ `ab - round(ab) ≥ 6^63 - frac(round(ab) / c)*c`

Since `round(ab) < c * 2^(k+1) ≤ 2^k * 2^64`, `round(ab)` rounds to an ulp of at most `2^k`,
and as such `ab - round(ab) ≤ 2^(k-1)`. Combining with the above, we derive

`2^(k-1) ≥ ab - round(ab) ≥ 6^63 - frac(round(ab) / c)*c > 2^63 - (1 - 2^(k-64))*c`

which rearranges to

`2c + (1 - c/2^63)*2^k > 2^64`.

Noting that `1 - c/2^63` is always non-negative, and using `k < 63`, this implies

`2c + (1 - c/2^63)*2^63 > 2^64`

or `c > 2^63`, which is a contradiction.
