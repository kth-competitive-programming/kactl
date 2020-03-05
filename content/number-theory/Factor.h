/**
 * Author: chilli, SJTU, pajenegod
 * Date: 2020-03-04
 * License: CC0
 * Source: own
 * Description: Pollard-rho randomized factorization algorithm. Returns prime
 * factors of a number, in arbitrary order (e.g. 2299 -> \{11, 19, 11\}).
 * Time: $O(n^{1/4})$ gcd calls, less for numbers with small factors.
 * Details: This implementation uses the improvement described here: https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Variants, where one can accumulate gcd calls by some factor (40 chosen here through exhaustive testing). This improves performance by approximately 6-10x depending on the inputs and speed of gcd. Benchmark found here: https://ideone.com/nGGD9T
 * GCD can improved by a factor of 1.75x using Binary GCD (https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/). However, with the gcd accumulation the bottleneck moves from the gcd calls to the mod_mul. As GCD only constitutes ~12% of runtime, speeding it up doesn't matter so much.
 * This code can probably be sped up by using a faster mod mul - potentially montgomery reduction on 128 bit integers.
 * Alternatively, one can use a quadratic sieve for an asymptotic improvement, which starts being factor in practice around 1e13.
 * Brent's cycle finding algorithm was tested. It reduces f calls by a small amount in exchange for a significant increase in gcd calls.
 */
#pragma once

#include "ModMulLL.h"
#include "MillerRabin.h"

ull pollard(ull n) {
	auto f = [n](ull x) { return mod_mul(x, x, n) + 1; };
	if (!(n & 1)) return 2;
	ull x = 0, y = 0, tim = 0, prd = 1, i = 1, tmp;
	for (; prd; y = f(f(y)), x = f(x)) {
		if (x == y || ++tim == 40) {
			tim = 0;
			if ((prd = __gcd(prd, n)) > 1) return prd;
			while (x == y) x = ++i, y = f(x);
		}
		tmp = prd, prd = mod_mul(prd, n + y - x, n);
	}
	return __gcd(tmp, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}
