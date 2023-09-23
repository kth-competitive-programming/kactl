/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$. If there are multiple solutions, an arbitrary one is returned.
 *  Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost, B are the m - rank solutions for Ax = 0.
 *  T has to have +, -, *, /, val
 * Time: O(n^2 m)
 * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
 */
#pragma once
template<class T> int SolveLinear(vector<vector<T>>& A, 
        vector<vector<T>>& B, vector<T>& b, vector<T>& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		T bv = T(0);
		rep(r,i,n) rep(c,i,m)
			if (A[r][c].val() > 0)
				br = r, bc = c, bv = A[r][c];
		if (bv.val() == 0) {
			rep(j,i,n) if (abs(b[j].val()) > 0) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
        rep(j, i+1, m) A[i][j] = A[i][j] / A[i][i];
        b[i] = b[i] / A[i][i];
        A[i][i] = T(1);
		rep(j,0,n) if(j != i){
			T fac = A[j][i];
			b[j] = b[j] - fac * b[i];
			rep(k,i,m) A[j][k] = A[j][k] - (fac*A[i][k]);
		}
		rank++;
	}
	x.assign(m, T(0));

    // Get Homo Solutions
    B.clear();
    rep(i, rank, m) {
        vector<T> sol(m);
        rep(j, 0, rank) sol[col[j]] = (A[j][i] * T(mod - 1));
        rep(j, rank, m) sol[col[j]] = (j == i ? 1 : 0);
        B.push_back(sol);
    }
    // matrix A is lost
	for (int i = rank; i--;) {
		b[i] = b[i] / A[i][i];
		x[col[i]] = b[i];
		rep(j,0,i) b[j] = b[j] - A[j][i] * b[i];
	}
	return rank; // (multiple solutions if rank < m)
}

