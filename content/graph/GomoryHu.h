/**
 * Author:
 * Description: Given a list of edges representing an undirected flow graph,
 * returns edges of the Gomory-Hu tree. The max flow between any pair of
 * vertices is given by minimum edge weight along the Gomory-Hu tree path.
 * Usage: 0-base index. GomoryHuTree t; auto ret = t.solve(n, edges); 0 is root, ret[i] for $i > 0$ contains (cost, par)
 * Time: $O(V)$ Flow Computations, $V = 3000, E = 4500$ and special graph that flow always terminate in O(3(V+E)) time in 4036ms.
 */
#pragma once

struct Edge {
    int s, e, x;
};

const int MAX_N = 500 + 1;

bool vis[MAX_N];

struct GomoryHuTree {
    vector<pii> solve(int n, const vector<Edge>& edges) { // i - j cut : i - j minimum edge cost. 0 based.
        vector<pii> ret(n); // if i > 0, stores pair(cost, parent)
        for(int i=1; i<n; i++){
            Dinic g(n);
            for (auto[s, e, x]: edges) g.add_edge(s, e, x, x);
            ret[i].first = g.max_flow(i, ret[i].second);
            
            memset(vis, 0, sizeof(vis));
            function<void(int)> dfs = [&](int x) {
                if (vis[x]) return;
                vis[x] = 1;
                for (auto& i: g.adj[x]) {
                    if (i.cap - i.flow > 0) dfs(i.a);
                }
            };

            dfs(i);
            for (int j=i+1; j<n; j++) {
                if (ret[j].second == ret[i].second && vis[j]) ret[j].second = i;
            }
        }            
        return ret;
    }
};
