/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with guaranteed complexity $O(V^2E)$.
 * On bipartite graphs the complexity is $O(\sqrt{V}E)$, and on unit graphs $O(\min(V^{1/2}, E^{2/3})E)).
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING
 */
template<class T=int> struct Dinic {
	const T INF = numeric_limits<T>::max();
	struct edge {
		int to, rev;
		T c, f;
	};
	vi lvl, ptr;
	vector<vector<edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), adj(n) {}
	void addEdge(int a, int b, T c, int rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, 0});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, 0});
	}
	T dfs(int v, T f, int t) {
		if (v == t || !f) return f;
		for (; ptr[v] < sz(adj[v]); ptr[v]++) {
			edge &e = adj[v][ptr[v]];
			if (lvl[e.to] != lvl[v] + 1) continue;
			if (T p = dfs(e.to, min(f, e.c - e.f), t)) {
				e.f += p, adj[e.to][e.rev].f -= p;
				return p;
			}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0;
		while(true) {
			fill(all(ptr), 0), fill(all(lvl), -1), lvl[s] = 0;
			queue<int> q({s});
			while (!q.empty() && lvl[t] == -1) {
				int v = q.front();
				q.pop();
				trav(e, adj[v])
					if (lvl[e.to] == -1 && e.f < e.c)
						q.push(e.to), lvl[e.to] = lvl[v] + 1;
			}
			if(lvl[t] == -1) return flow;
			while (T p = dfs(s, INF, t)) flow += p;
		}
	}
};