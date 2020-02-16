#include "../utilities/template.h"
#include "../utilities/genTree.h"

#include "../../content/graph/LCA.h"
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
		vector<tuple<int, int, int, ll>> q(1);
		vpi ret;
		int T = 0, v, p, d; ll di;
		while (!q.empty()) {
			tie(v, p, d, di) = q.back();
			q.pop_back();
			if (d) ret.emplace_back(d, p);
			time[v] = T++;
			dist[v] = di;
			trav(e, C[v]) if (e.first != p)
				q.emplace_back(e.first, v, d+1, di + e.second);
		}
		return ret;
	}

	int query(int a, int b) {
		if (a == b) return a;
		a = time[a], b = time[b];
		return rmq.query(min(a, b), max(a, b)).second;
	}
	ll distance(int a, int b) {
		int lca = query(a, b);
		return dist[a] + dist[b] - 2 * dist[lca];
	}
};
}

void test_n(int n, int num) {
    for (int out=0; out<num; out++) {
        auto graph = genRandomTree(n);
        vector<vector<pair<int, int>>> tree(n);
        for (auto i: graph) {
            tree[i.first].push_back({i.second, 1});
            tree[i.second].push_back({i.first, 1});
        }

        LCA lca(tree);
        old::LCA old_lca(tree);
        for (int i=0; i<100; i++) {
            int a = rand()%n, b = rand()%n;
            assert(lca.distance(a,b) == old_lca.distance(a,b));
        }
    }

}
signed main() {
    test_n(10, 1000);
    test_n(100, 100);
    test_n(1000, 10);
    cout<<"Tests passed!"<<endl;
}

