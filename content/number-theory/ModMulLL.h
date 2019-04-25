/**
 * Author: chilli, Ramchandra Apte
 * Date: 2019-04-24
 * License: MIT
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/modulo.h
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $c < 2^63$.
 * a and b must lie in the range [0, mod) before input.
 * Time: O(1) for mod_mul, O(log b) for mod_pow
 */
#pragma once

typedef unsigned long long ull;
typedef long double ld;
ull mod_mul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ret + M * ((ret < 0) - (ret >= (ll)M));
}
ull mod_pow(ull a, ull b, ull mod) {
	if (b == 0) return 1;
	ull res = mod_pow(a, b / 2, mod);
	res = mod_mul(res, res, mod);
	if (b & 1) return mod_mul(res, a, mod);
	return res;
}
