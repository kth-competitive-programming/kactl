/**
 * Author: Simon Lindholm
 * Date: 2016-09-10
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: Can be used for convolutions modulo specific nice primes
 * of the form $2^a b+1$, where the convolution result has size at most $2^a$.
 * For other primes/integers, use two different primes and combine with CRT.
 * Inputs must be in [0, mod)
 * Time: O(N \log N)
 * Status: Somewhat tested
 */
#pragma once

#include "../number-theory/ModPow.h"

const ll mod = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

typedef vector<ll> vl;
void ntt(vl &a, vl &rt, vl &rev, int n) {
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
			rep(j,0,k) {
				ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
				a[i + j + k] = z > ai ? ai - z + mod : ai - z;
				ai += ai + z >= mod ? z - mod : z;
			}
}

vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty())
		return {};
	int s = sz(a) + sz(b) - 1, L = 32 - __builtin_clz(s), n = 1 << L;
	vl L(a), R(b), out(n), rt(n, 1), rev(n);
	L.resize(n), R.resize(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	int curL = mod / 2;
	for (int k = 2; k < n; k *= 2) {
		ll z[] = {1, modpow(root, curL /= 2)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1 ] %mod;
	}
	ntt(L, rt, rev, n), ntt(R, rt, rev, n);
	ll inv = modpow(n, mod - 2);
	rep(i,0,n) out[-i&(n-1)] = L[i] * R[i] % mod * inv % mod;
	ntt(out, rt, rev, n);
	return {out.begin(), out.begin() + s};
}
