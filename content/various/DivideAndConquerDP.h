/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: Codeforces
 * Description: Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal)
 * optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
 * Time: O((N + (hi-lo)) \log N)
 * Status: tested on http://codeforces.com/contest/321/problem/E
 */
#pragma once

struct DP { // Modify at will:
	ll lo(ll ind) { return 0; }
	ll hi(ll ind) { return ind; }
	ll f(ll ind, ll k) { return dp[ind][k]; }
	void store(ll ind, ll k, ll v) { res[ind] = pii(k, v); }

	void rec(ll L, ll R, ll LO, ll HI) {
		if (L >= R) return;
		ll mid = (L + R) >> 1;
		pair<ll, ll> best(LLONG_MAX, LO);
		rep(k, max(LO,lo(mid)), min(HI,hi(mid)))
			best = min(best, make_pair(f(mid, k), k));
		store(mid, best.second, best.first);
		rec(L, mid, LO, best.second+1);
		rec(mid+1, R, best.second, HI);
	}
	void solve(ll L, ll R) { rec(L, R, INT_MIN, INT_MAX); }
};
