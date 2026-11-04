/**
 * Author: Adam Soltan
 * Date: 2026-01-13
 * License: CC0
 * Description: Fast bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $r$ should be a vector full of
 * $-1$'s of the same size as the right partition. Returns the size of
 * the matching. $r[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Time: O(E \sqrt{V})
 * Status: stress-tested by MinimumVertexCover and tested on Library Checker
 */
#pragma once

int hopcroftKarp(vector<vi>& g, vi& r) {
	int n = sz(g), res = 0;
	vi l(n, -1), q(n), d(n);
	auto dfs = [&](auto f, int u) -> bool {
		int t = exchange(d[u], 0) + 1;
		for (int v : g[u])
			if (r[v] == -1 || (d[r[v]] == t && f(f, r[v])))
				return l[u] = v, r[v] = u, 1;
		return 0;
	};
	for (int t = 0, f = 0;; t = f = 0, d.assign(n, 0)) {
		rep(i,0,n) if (l[i] == -1) q[t++] = i, d[i] = 1;
		rep(i,0,t) for (int v : g[q[i]]) {
			if (r[v] == -1) f = 1;
			else if (!d[r[v]]) d[r[v]] = d[q[i]] + 1, q[t++] = r[v];
		}
		if (!f) return res;
		rep(i,0,n) if (l[i] == -1) res += dfs(dfs, i);
	}
}
