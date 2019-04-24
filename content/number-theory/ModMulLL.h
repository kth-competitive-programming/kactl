/**
 * Author: Lukas Polacek
 * Date: 2010-01-26
 * License: CC0
 * Source: TopCoder tutorial
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for large $c$.
 * Time: O(64/bits \cdot \log b), where $bits = 64-k$, if we want to deal with
 * $k$-bit numbers.
 */
#pragma once

typedef unsigned long long ull;
typedef long double ld;
ull mod_mul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull mod_pow(ull a, ull b, ull mod) {
	if (b == 0) return 1;
	ull res = mod_pow(a, b / 2, mod);
	res = mod_mul(res, res, mod);
	if (b & 1) return mod_mul(res, a, mod);
	return res;
}
