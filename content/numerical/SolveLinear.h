/**
 * Author: Per Austrin
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: Solves $A * x = b$, or as much of $x$ as possible. Returns rank.
 * Data in $A$ and $b$ is lost.
 * Time: O(n^3)
 * Usage: double A[3][3], b[3], x[3];
 int rank = solve_linear(3,A,b,x);
 * Status: Unknown
 */
#pragma once

#include <cmath>
#include <algorithm>
using namespace std;

const double undefined = 1.0/0.0;
const double eps = 1e-12;

template <int N> int
solve_linear(int n, double A[N][N], double b[N], double x[N]) {
	int row[N], col[N], undef[N], invrow[N], invcol[N], rank = 0;
	rep(i,0,n) row[i] = col[i] = i, undef[i] = false;

	for (int i = 0; i < n; rank = ++i) {
		int br = i, bc = i;
		double v, bv = fabs(A[row[i]][col[i]]);
		rep(r,i,n) rep(c,i,n)
			if ((v = fabs(A[row[r]][col[c]])) > bv)
				br = r, bc = c, bv = v;
		if (bv < eps) break;
		if (i != br) swap(row[i], row[br]);
		if (i != bc) swap(col[i], col[bc]);
		rep(j,i+1,n) {
			double fac = A[row[j]][col[i]] / bv;
			A[row[j]][col[i]] = 0;
			b[row[j]] -= fac * b[row[i]];
			rep(k,i+1,n) A[row[j]][col[k]]-=fac*A[row[i]][col[k]];
		}
	}

	for (int i = rank; i--; ) {
		b[row[i]] /= A[row[i]][col[i]];
		A[row[i]][col[i]] = 1;
		rep(j,rank,n) if(fabs(A[row[i]][col[j]]) > eps)
			undef[i] = true;
		for (int j = i - 1; j >= 0; --j) {
			if (undef[i] && fabs(A[row[j]][col[i]]) > eps)
				undef[j] = true;
			else {
				b[row[j]] -= A[row[j]][col[i]] * b[row[i]];
				A[row[j]][col[i]] = 0;
			}
		}
	}

	rep(i,0,n) invrow[row[i]] = i, invcol[col[i]] = i;
	rep(i,0,n) if(invrow[i] >= rank || undef[invrow[i]])
		b[i] = undefined;
	rep(i,0,n) x[i] = b[row[invcol[i]]];
	return rank;
}
