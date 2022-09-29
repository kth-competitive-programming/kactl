/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once

struct Dinic {
	struct E {
		int v, r;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	int n;
	vi le, it, q;
	vector<vector<E>> adj;
	Dinic(int n): n(n), le(n), it(n), q(n), adj(n) {}
	void addEdge(int u, int v, ll c, ll rc = 0) {
		adj[u].push_back({u, sz(adj[v]), c, c});
		adj[v].push_back({v, sz(adj[u]) - 1, rc, rc});
	}
	ll dfs(int u, int t, ll f) {
		if (u == t || !f) return f;
		for (int &i = ptr[u]; i < sz(adj[u]); ++i) {
			auto &[v, r, c, oc] = adj[u][i];
			if (le[v] == le[u] + 1)
				if (ll p = dfs(v, min(f, c))) {
					c -= p, adj[v][r].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			le = it = vi(sz(q));
			int qi = 0, qe = le[s] = 1;
			while (qi < qe && !le[t]) {
				int v = q[qi++];
				for (auto [v, r, c, oc]: adj[u])
					if (!le[v] && c >> (30 - L))
						q[qe++] = v, le[v] = le[u] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (le[t]);
		return flow;
	}
	bool leftOfMinCut(int u) { return le[u] != 0; }
};
