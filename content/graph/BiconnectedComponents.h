/**
 * Author:
 * Description: Find all biconnected component made by cutting bridge. Hence each bcc is maximal biconnected component. Arctic edges are every bcc that its size equals to 2. Arctic nodes are every node that it belongs to at least 2 different rbcc.
 * Usage: 1-base index (0 use as dummy parent). if (!dfn[i]) dfs(i, 0); bcc[color] stores nodes contained in that bcc. Valid bcc number is [1, c].
 * Time: O(V+E), $V = E = 5 \times 10^5$ in 500ms at yosupo, $V = 10^5, E = 10^6$ in 216ms at BOJ.
 */
#pragma once

const int MAX_N = 5e5 + 1;

vector<int> adj[MAX_N];
vector<int> bcc[MAX_N];
vector<int> st;
int low[MAX_N], dfn[MAX_N];
int piv = 0, c = 0;

void dfs(int x, int p){
    if (adj[x].empty()) {
        bcc[++c].push_back(x);
        return;
    }
    
    dfn[x] = low[x] = ++piv;
    st.push_back(x);
    for (auto v: adj[x]) {
        if (!dfn[v]) {
            dfs(v, x);
            low[x] = min(low[x], low[v]);
            if (low[v] >= dfn[x]) {
                bcc[++c].push_back(x);
                while (!st.empty()) {
                    int tmp = st.back();
                    bcc[c].push_back(tmp);
                    st.pop_back();
                    if (tmp == v) break;
                }
            }
        } else {
            low[x] = min(low[x], dfn[v]);
        }
    }
}
