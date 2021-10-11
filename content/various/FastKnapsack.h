/**
 * Author: Mårten Wiman
 * License: CC0
 * Source: Pisinger 1999, "Linear Time Algorithms for Knapsack Problems with Bounded Weights"
 * Description: Given N non-negative integer weights w and a non-negative target t,
 * computes the maximum S <= t such that S is the sum of some subset of the weights.
 * Time: O(N \max(w_i))
 * Status: Tested on kattis:eavesdropperevasion, stress-tested
 */
#pragma once

int knapsack(vi w, int t) {
	int a = 0, b = 0, j;
	while (b < sz(w) && a + w[b] <= t) a += w[b++];
	if (b == sz(w)) return a;
	int m = *max_element(all(w));
	vi u(m*2+1, -1), v = u;
	u[a+m-t] = b+1;
	rep(i,b,sz(w)) {
		rep(x,0,m) v[x+w[i]] = max(v[x+w[i]], u[x]);
		for (int x = 2*m; x > m; x--)
			for(j = v[x]; j --> u[x];) v[x-w[j]] = max(v[x-w[j]], j);
		u = v;
	}
	for (int i = t; i > a; i--)
		if (v[i+m-t] >= 0) return i;
	return a;
}