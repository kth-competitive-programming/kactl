/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow. cap[i][j] != cap[j][i] is allowed; double edges are not.
 *  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: Approximately O(E^2)
 */
#pragma once

// #include <bits/extc++.h> /// include-line, keep-include

const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;

struct MCMF {
	struct edge
	{
		int from, to, rev;
		ll cap, cost, flow;
	};
	int N;
	vector<vector<edge>> ed;
	vi seen, ind;
	vi dist, pi;
	vector<edge*> par;

	MCMF(int N) :
		N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		if (from == to) return;
		ed[from].emplace_back(edge{ from,to,sz(ed[to]),cap,cost,0});
		ed[to].emplace_back(edge{ to,from,sz(ed[from])-1,0,-cost,0});
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), inf);
		dist[s] = 0; ll di;

		//priority_queue<pair<ll, int>> q;
		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({ 0, s });

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to])
			{
				ll val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == q.end()) its[e.to] = q.push({ -dist[e.to], e.to });
					else q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		rep(i, 0, N) pi[i] = min(pi[i] + dist[i], inf);
	}

	pair<ll, ll> maxflow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = inf;
			for (int p, x = t; par[x] && (p = par[x]->from, x != s); x = p)
				fl = min(fl, par[x]->cap - par[x]->flow);

			totflow += fl;
			for (int p, x = t; par[x] && (p = par[x]->from, x != s); x = p)
			{
				par[x]->flow += fl;
				ed[par[x]->to][par[x]->rev].flow -= fl;
			}
		}
		rep(i, 0, N) for (edge& e : ed[i]) totcost += e.cost * e.flow;
		return { totflow, totcost/2 };
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), inf); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i, 0, N) if (pi[i] != inf)
				for (edge& e : ed[i]) if (e.cap)
					if ((v = pi[i] + e.cost) < pi[e.to])
						pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};
