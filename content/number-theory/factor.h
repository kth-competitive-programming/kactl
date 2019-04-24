/**
 * Author: Lukas Polacek
 * Date: 2010-01-28
 * License: CC0
 * Source: Wikipedia
 * Description: Pollard's rho algorithm. It is a probabilistic factorisation
 * algorithm, whose expected time complexity is good. Before you start using it,
 * run {\tt init(bits)}, where bits is the length of the numbers you use.
 * Returns factors of the input without duplicates.
 * Time: Expected running time should be good enough for 50-bit numbers.
 */
#pragma once

#include "ModMulLL.h"
#include "MillerRabin.h"

ull f(ull x, ull n) { return (mod_mul(x, x, n) + 1) % n; }
ull Pollard(ull n) {
	if (isPrime(n)) return n;
	if (!(n & 1)) return 2;
	rep(i,2,50) {
		ull x = i, y = f(x, n), p = __gcd(n + y - x, n);
		while (p == 1)
			x = f(x, n), y = f(f(y, n), n), p = __gcd(n + y - x, n);
		if (p == n) continue;
		return p;
	}
	return 0;
}
vector<ull> factor(ull n) {
	if (n==1) return {};
    ull x = Pollard(n);
    if (x == n)
        return {x};
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}