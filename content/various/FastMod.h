/**
 * Author: Simon Lindholm
 * Date: 2019-04-19
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Barrett_reduction
 * Description: Compute $a \% b$ about 4 times faster than usual, where $b$ is constant but not known at compile time.
 * Fails for $b = 1$.
 * Status: proven correct, stress-tested
 * Measured as having 3 times lower latency, and 8 times higher throughput.
 */
#pragma once

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64), r = a - q * b;
		return r >= b ? r - b : r;
	}
};
