/**
 * Author: chilli, Bjarki Ágúst Guðmundsson
 * Date: 2019-05-10
 * License: MIT
 * Source: https://github.com/SuprDewd/CompetitiveProgramming/blob/master/code/graph/arborescence.cpp
 * Description: The Edmonds/Chuliu algorithm for finding the minimum spanning
 * tree/arborescence in a directed graph. Returns (weight, edge indices) where
 * the edges are indexed by order of insertion. If no MST exists, returns
  * weight=-1;
 * Time: O(VE)
 * Status: Tested on CF 240E
 */

#include "../data-structures/UnionFind.h"
struct DMST {
	int n, m = 0;
	UF uf;
	struct edge { int a, b, w, id=-1; };
	typedef vector<edge> ve;
	vector<ve> adj;
	ve edges;
	DMST(int _n) : n(_n), uf(n), adj(n) {}
	void add_edge(int a, int b, int c) {
		edges.push_back({a,b,c,m++});
		adj[b].push_back(edges.back());
	}
	ve find_min(int r) {
		vi vis(n, -1), mn(n, 1e9);
		ve par(n);
		rep(i,0,n) {
			if (uf.find(i) != i) continue;
			int at = i;
			while (at != r && vis[at] == -1) {
				vis[at] = i;
				trav(v, adj[at])
					if (v.w < mn[at] && uf.find(v.a) != at)
						mn[at] = v.w, par[at] = v;
				if (par[at].id == -1) return {};
				at = uf.find(par[at].a);
			}
			if (at == r || vis[at] != i) continue;
			UF tmp = uf;
			vi seq;
			do seq.push_back(at);
			while ((at = uf.find(par[at].a)) != seq.front());
			trav(v, seq) uf.join(v, seq[0]);
			int c = uf.find(seq[0]);
			ve nw;
			trav(v, seq) trav(w, adj[v])
				nw.push_back({w.a, w.b, w.w-mn[v], w.id});
			adj[c] = nw;
			auto rest = find_min(r);
			if (sz(rest) == 0) return {};
			auto use = rest[c];
			rest[at = tmp.find(use.b)] = use;
			trav(v, seq) if (v != at) rest[v] = par[v];
			return rest;
		}
		return par;
	}
	pair<int, vi> mst(int r) {
		auto res = find_min(r);
		if (res.empty()) return {-1, {}};
		int sm=0;
		vi ans;
		rep(i,1,sz(res))
			sm += edges[res[i].id].w, ans.push_back(res[i].id);
		return {sm, ans};
	}
};
