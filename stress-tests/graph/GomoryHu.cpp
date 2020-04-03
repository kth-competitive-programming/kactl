#include "../utilities/template.h"
#include "../utilities/utils.h"

#include "../../content/graph/GomoryHu.h"
#include "../../content/graph/Dinic.h"


void test(int N, int mxFlow, int iters) {
    for (int it = 0; it < iters; it++) {
        int n = rand()%N+1;
        vector<array<ll, 3>> edges;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                edges.push_back({i, j, rand() % mxFlow});
            }
        }
        auto calc = [&](int s, int t) {
            Dinic flow(n);
            for (auto e : edges) {
                flow.addEdge(e[0], e[1], e[2], e[2]);
            }
            return flow.calc(s, t);
        };
        vector<Edge> gomoryHuTree = gomoryHu(n, edges);
        vector<vector<array<int, 2>>> adj(n);
        for (auto e : gomoryHuTree) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
        auto dfs = make_y_combinator([&](auto dfs, int start, int cur, int p, int mn) -> void {
            if (start != cur) {
                assert(mn == calc(start, cur));
            }
            for (auto i : adj[cur]) {
                if (i[0] != p)
                    dfs(start, i[0], cur, min(mn, i[1]));
            }
        });
        dfs(0, 0, -1, 1e9);
    }
}
signed main() {
    test(25, 5, 105);
    test(100, 1000, 5);
    test(100, 1, 50);
    test(5, 5, 10000);
    cout<<"Tests passed!"<<endl;
}
