/**
 * Author: chilli, Ramchandra Apte
 * Date: 2019-04-24
 * License: MIT
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/modulo.h
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $0 \le a, b < c < 2^{63}$.
 * Time: O(1) for \texttt{mod\_mul}, O(\log b) for \texttt{mod\_pow}
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
	return b & 1? mod_mul(res, a, mod) : res;
}
