/**
 * Author:
 * Description: Undirected graph with adj matrix. No edge means $adj[i][j] = 0$.
 * 0-based index, and expect $N \times N$ adj matrix.
 * Time: O(V^3), $\sum V^3 = 5.5 \times 10^8$ in 640ms.
 */
#pragma once

const int INF = 1e9;
int getMinCut(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> used(n);
    int ret = INF;
    for (int ph=n-1; ph>=0; --ph) {
        vector<int> w = adj[0], added = used;
        int prev, k = 0;
        for (int i=0; i<ph; ++i) {
            prev = k;
            k = -1;
            for (int j = 1; j < n; j++) {
                if (!added[j] && (k == -1 || w[j] > w[k])) k = j;
            }
            if (i+1 == ph) break;
            for (int j = 0; j < n; j++) w[j] += adj[k][j];
            added[k] = 1;
        }
        for (int i=0; i<n; ++i) adj[i][prev] = (adj[prev][i] += adj[k][i]);
        used[k] = 1;
        ret = min(ret, w[k]);
    }
    return ret;
}
