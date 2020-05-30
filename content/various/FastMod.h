/**
 * Author: Simon Lindholm
 * Date: 2019-04-19
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Barrett_reduction
 * Description: Compute $a \% b$ about 4 times faster than usual, where $b$ is constant but not known at compile time.
 * \vspace{0.5mm}
 * Status: proven correct, stress-tested
 * Measured as having 3 times lower latency, and 8 times higher throughput.
 */
#pragma once

typedef unsigned long long ull;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) {
		ull q = (ull)((__uint128_t(m) * a) >> 64), r = a - q * b;
		return r - (r >= b) * b;
	}
};
