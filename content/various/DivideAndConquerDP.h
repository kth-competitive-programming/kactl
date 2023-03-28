/**
 * Author: Vidit Jain
 * License: CC0
 * Source: CP-Algorithms
 * Description: Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal) optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
 * Time: O((N + (hi-lo)) \log N)
 * Status: tested on https://codeforces.com/contest/833/problem/B
 */
#pragma once

template<typename T>
struct DP{
    int n, m;
	T id;
    vector<T> dp[2];
    DP (int n, int m, T id) : n(n), m(m), id(id), dp{vector<T>(n), vector<T>(n)}{}
    T C(int i, int j, int ind) {return (i ? dp[ind^1][i-1] : 0);}
    void rec(int l, int r, int optl, int optr, int ind) {
        if (l > r) return;
        int mid = (l + r) >> 1;
        pair<T,int> best = {id, optl};
        rep (k, optl, min(mid, optr)+1)
            best = min(best, {C(k, mid, ind), k});
        dp[ind][mid] = best.ff;
        rec(l, mid-1, optl, best.ss, ind), rec(mid+1, r, best.ss, optr, ind);
    }
    T solve() {
        rep(i, 0, n)
            dp[0][i] = C(0, i, 0);
        rep(i, 1, m)
            rec(0, n-1, 0, n-1, i&1);
        return dp[(m-1)&1][n-1];
    }
};
