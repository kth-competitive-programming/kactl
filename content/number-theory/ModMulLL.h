/**
 * Author: chilli, Ramchandra Apte, Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/modulo.h
 * Proof of correctness is in doc/modmul-proof.md.
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $0 \le a, b < c < 2^{63}$.
 * Time: O(1) for \texttt{mod\_mul}, O(\log b) for \texttt{mod\_pow}
 * Status: stress-tested, proven correct
 */
#pragma once

typedef unsigned long long ull;
typedef long double ld;
ull mod_mul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull mod_pow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = mod_mul(b, b, mod), e /= 2)
		if (e & 1) ans = mod_mul(ans, b, mod);
	return ans;
}
