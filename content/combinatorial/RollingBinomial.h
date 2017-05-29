/**
 * Author: Simon Lindholm
 * Date: 2015-03-02
 * License: CC0
 * Source: own work
 * Description: $\binom{n}{k}\text{ (mod m)}$ in time proportional to the difference between (n, k) and the previous (n, k).
 * Status: tested
 */
#pragma once

const ll mod = 1000000007;
vector<ll> invs; // precomputed up to max n, inclusively
struct Bin {
	int N = 0, K = 0;  ll r = 1;
	void m(ll a, ll b) { r = r * a % mod * invs[b] % mod; }
	ll choose(int n, int k) {
		if (k > n || k < 0) return 0;
		while (N < n) ++N, m(N, N-K);
		while (K < k) ++K, m(N-K+1, K);
		while (K > k) m(K, N-K+1), --K;
		while (N > n) m(N-K, N), --N;
		return r;
	}
};
