/**
 * Author: sharaelong
 * Description: Undirected connected graph, no self-loop. Find every bridges. Usual graph representation.
 * dfs(here, par): returns fastest vertex which connected by some node in subtree of here, except here-parent edge.
 * Time: O(V+E), 180ms for $V = 10^5$ and $E = 10^6$ graph.
 * Status: stress-tested
 */
#pragma once

const int MAX_N = 1e5 + 1;

vector<int> adj[MAX_N];
vector<pii> bridges;
int in[MAX_N];
int cnt = 0;

int dfs(int here, int parent = -1) {
    in[here] = cnt++;
    int ret = 1e9;
    for (int there: adj[here]) {
        if (there != parent) {
            if (in[there] == -1) {
                int subret = dfs(there, here);
                if (subret > in[here]) bridges.push_back({here, there});
                ret = min(ret, subret);
            } else {
                ret = min(ret, in[there]);
            }
        }
    }
    return ret;
}
