/**
 * Author:
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: Invert matrix $A$. Result is stored in $A$.
 * Can easily be extended to prime moduli; for prime powers, repeatedly
 * set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(n^3)
 * Usage: double A[3][3];
 bool singular = matrix_inverse(A,3);
 * Status: Unknown
 */
#pragma once

#include <cmath>
#include <algorithm>
using namespace std;

template <int N> bool matrix_inverse(double A[N][N], int n) {
	int row[N], col[N], invcol[N]; double tmp[N][N] ;
	memset(tmp, 0, sizeof(tmp));
	rep(i,0,n) tmp[i][i] = 1, row[i] = col[i] = i;

	rep(i,0,n) { // forward pass:
		int r = i, c = i; // find pivot
		rep(j,i,n) rep(k,i,n)
			if (fabs(A[row[j]][col[k]]) > fabs(A[row[r]][col[c]]))
				r = j, c = k;
		if (fabs(A[row[r]][col[c]]) < 1e-12) // pivot found?
			return false; // if singular
		if (i != r) swap(row[i], row[r]); // pivot
		if (i != c) swap(col[i], col[c]);
		double v = A[row[i]][col[i]]; // eliminate forward
		rep(j,i+1,n) {
			double f = A[row[j]][col[i]] / v;
			A[row[j]][col[i]] = 0;
			rep(k,i+1,n) A[row[j]][col[k]] -= f*A[row[i]][col[k]];
			rep(k,0,n) tmp[row[j]][col[k]] -= f*tmp[row[i]][col[k]];
		} // normalize row
		rep(j,i+1,n) A[row[i]][col[j]] /= v;
		rep(j,0,n) tmp[row[i]][col[j]] /= v;
		A[row[i]][col[i]] = 1;
	}

	for (int i = n-1; i > 0; --i) // backward pass:
	for (int j = i-1; j >= 0; --j) {
		double v = A[row[j]][col[i]];
		// forget A at this point, just eliminate tmp backward
		rep(k,0,n) tmp[row[j]][col[k]] -= v*tmp[row[i]][col[k]];
	}

	rep(i,0,n) invcol[col[i]] = i;
	rep(i,0,n) rep(j,0,n) A[i][j] = tmp[row[invcol[i]]][j];
	return true;
}
