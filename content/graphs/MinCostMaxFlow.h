/**
 * Author: Tyler M
 * Date: 2/2/2024
 * Source: various cf blogs
 * Description: Min-cost max-flow. Negative cost cycles not supported.
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis:mincostmaxflow, various CSES problems and 
 * 	Petra problems
 * Time: Approximately $O(E^2)$, actually $O(FS)$ where S is the time
 * 	complexity of the SSSP alg used in find path (in this case SPFA)
 */
#pragma once

struct mcmf {
	const ll inf = LLONG_MAX >> 2;
	struct edge {
		int v;
		ll cap, flow, cost;
	};
	int n;
	vector<edge> edges;
	vvi adj; vii par; vi in_q;
	vector<ll> dist, pi;
	mcmf(int n): n(n), adj(n), dist(n), pi(n), par(n), in_q(n) {}
	void add_edge(int u, int v, ll cap, ll cost) {
		int idx = sz(edges);
		edges.push_back({v, cap, 0, cost});
		edges.push_back({u, cap, cap, -cost});
		adj[u].push_back(idx);
		adj[v].push_back(idx ^ 1);
	}
	bool find_path(int s, int t) {
		fill(all(dist), inf);
		fill(all(in_q), 0);
		queue<int> q; q.push(s); 
		dist[s] = 0, in_q[s] = 1;
		while(!q.empty()) {
			int cur = q.front(); q.pop();
			in_q[cur] = 0;
			for(int idx: adj[cur]) {
				auto [nxt, cap, fl, wt] = edges[idx];
				ll nxtD = dist[cur] + wt;
				if(fl >= cap || nxtD >= dist[nxt]) continue;
				dist[nxt] = nxtD;
				par[nxt] = {cur, idx};
				if(in_q[nxt]) continue;
				q.push(nxt); in_q[nxt] = 1;
			}
		}
 
		return dist[t] < inf;
	}
	pair<ll, ll> calc(int s, int t) {
		ll flow = 0, cost = 0;
		while(find_path(s, t)) {
			rep(i, 0, n) pi[i] = min(pi[i] + dist[i], inf);
			ll f = inf;
			for(int i, u, v = t; tie(u, i) = par[v], v != s; v = u)
				f = min(f, edges[i].cap - edges[i].flow);
			flow += f;
			for(int i, u, v = t; tie(u, i) = par[v], v != s; v = u)
				edges[i].flow += f, edges[i^1].flow -= f;
		}
		rep(i, 0, sz(edges)>>1)
			cost += edges[i<<1].cost * edges[i<<1].flow;
 
		return {flow, cost};
	}
};