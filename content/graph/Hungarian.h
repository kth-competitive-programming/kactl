/**
 * Author:
 * Description: Bipartite minimum weight matching.
 * 1-base indexed. A[1..n][1..m] and $n \leq m$ needed. pair(cost, matching) will be returned.
 * Usage: auto ret = hungarian(A);
 * Time: O(n^2m), and 100ms for n = 500.
 */

const ll INF = 1e18;

pair<ll, vector<int>> hungarian(const vector<vector<ll>>& A) {
    int n = (int)A.size()-1;
    int m = (int)A[0].size()-1;
    vector<ll> u(n+1), v(m+1), p(m+1), way(m+1);
    for (int i=1; i<=n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<ll> minv (m+1, INF);
        vector<char> used (m+1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1;
            ll delta = INF;
            for (int j=1; j<=m; ++j) {
                if (!used[j]) {
                    ll cur = A[i0][j]-u[i0]-v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            }
            for (int j=0; j<=m; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vector<int> match(n+1);
    for (int i=1; i<=m; ++i) match[p[i]] = i;
    return { -v[0], match };
}
