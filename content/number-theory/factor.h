/**
 * Author: chilli, SJTU
 * Date: 2019-04-24
 * License: CC0
 * Source: https://github.com/FTRobbin/Dreadnought-Standard-Code-Library
 * Description: Pollard's rho algorithm. It is a probabilistic factorisation
 * algorithm, whose expected time complexity is good.
 * Time: On worst case numbers, $O(n^{1/4})$. Faster than that for most numbers.
 */
#pragma once

#include "ModMulLL.h"
#include "MillerRabin.h"

ull f(ull x, ull n) { return (mod_mul(x, x, n) + 1) % n; }
ull Pollard(ull n) {
	auto f = [&n](ull x) { return (mod_mul(x, x, n) + 1) % n; };
	if (isPrime(n)) return n;
	if (!(n & 1)) return 2;
	for (ull i = 2;; i++) {
		ull x = i, y = f(x), p = __gcd(n + y - x, n);
		while (p == 1)
			x = f(x), y = f(f(y)), p = __gcd(n + y - x, n);
		if (p != n) return p;
	}
	return 0;
}
vector<ull> factor(ull n) {
	if (n==1) return {};
	ull x = Pollard(n);
	if (x == n) return {x};
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}
