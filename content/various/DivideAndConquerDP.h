/**
 * Author: Vidit Jain
 * License: CC0
 * Source: CP-Algorithms
 * ExtDesc: Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal) optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
 * Description: Applicable if $(A[i][j] \leq A[i][j + 1])$. Quadrangle Inequality is also sufficient $(C[a][c] + C[b][d] \leq C[a][d] + C[b][c])$
 * Time: O(kN\log N)
 * Status: tested on https://codeforces.com/contest/833/problem/B
 */
#pragma once

template<typename T>
struct DP{
	int n, m;
	T id;
	using vt = vector<T>;
	vt dp[2];
	DP(int n, int m, T id):n(n), m(m), id(id), dp{vt(n),vt(n)}{}
	T C(int i, int j, int x) {return (i ? dp[x^1][i-1] : 0);}
	void rec(int l, int r, int optl, int optr, int x) {
		if (l > r) return;
		int mid = (l + r) >> 1;
		pair<T,int> best = {id, optl};
		rep (k, optl, min(mid, optr)+1)
			best = min(best, {C(k, mid, x), k});
		dp[x][mid] = best.ff;
		rec(l, mid-1, optl, best.ss, x), rec(mid+1, r, best.ss, optr, x);
	}
	T solve() {
		rep(i, 0, n)
			dp[0][i] = C(0, i, 0);
		rep(i, 1, m)
			rec(0, n-1, 0, n-1, i&1);
		return dp[(m-1)&1][n-1];
	}
};
