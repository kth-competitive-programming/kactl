#include "../utilities/template.h"
#include "../utilities/genTree.h"

#include "../../content/graph/LCA.h"
#include "../../content/graph/BinaryLifting.h"
#include "../../content/data-structures/RMQ.h"

namespace old {
typedef vector<pii> vpi;
typedef vector<vpi> graph;

struct LCA {
	vi time;
	vector<ll> dist;
	RMQ<pii> rmq;

	LCA(graph& C) : time(sz(C), -99), dist(sz(C)), rmq(dfs(C)) {}

	vpi dfs(graph& C) {
		vector<tuple<ll, ll, ll, ll>> q(1);
		vpi ret;
		ll T = 0, v, p, d; ll di;
		while (!q.empty()) {
			tie(v, p, d, di) = q.back();
			q.pop_back();
			if (d) ret.emplace_back(d, p);
			time[v] = T++;
			dist[v] = di;
			for(auto &e: C[v]) if (e.first != p)
				q.emplace_back(e.first, v, d+1, di + e.second);
		}
		return ret;
	}

	ll query(ll a, ll b) {
		if (a == b) return a;
		a = time[a], b = time[b];
		return rmq.query(min(a, b), max(a, b)).second;
	}
	ll distance(ll a, ll b) {
		ll lca = query(a, b);
		return dist[a] + dist[b] - 2 * dist[lca];
	}
};
}


void getPars(vector<vi> &tree, ll cur, ll p, ll d, vector<ll> &par, vector<ll> &depth) {
	par[cur] = p;
	depth[cur] = d;
	for(auto i: tree[cur]) if (i != p) {
		getPars(tree, i, cur, d+1, par, depth);
	}
}
void test_n(ll n, ll num) {
	for (ll out=0; out<num; out++) {
		auto graph = genRandomTree(n);
		vector<vi> tree(n);
		vector<vector<pair<ll, ll>>> oldTree(n);
		for (auto i: graph) {
			tree[i.first].push_back(i.second);
			tree[i.second].push_back(i.first);
			oldTree[i.first].push_back({i.second, 1});
			oldTree[i.second].push_back({i.first, 1});
		}
		vector<ll> par(n), depth(n);
		getPars(tree, 0, 0, 0, par, depth);
		vector<vi> tbl = treeJump(par);
		LCA new_lca(tree);
		old::LCA old_lca(oldTree);
		for (ll i=0; i<100; i++) {
			ll a = rand()%n, b = rand()%n;
			ll binLca = lca(tbl, depth, a, b);
			ll newLca = new_lca.lca(a,b);
			ll oldLca = old_lca.query(a,b);
			assert(oldLca == newLca);
			assert(binLca == newLca);
		}
	}
}

signed main() {
	test_n(10, 1000);
	test_n(100, 100);
	test_n(1000, 10);
	cout<<"Tests passed!"<<endl;
}

