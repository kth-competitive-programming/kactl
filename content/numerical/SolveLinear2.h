/**
 * Author: Per Austrin
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: Solves $A * x = b$, or as much of $x$ as possible.
 *  Returns rank, or -1 if there is no solution.
 *  Data in $A$ and $b$ is lost.
 *  When $x[i]$ has two possible values it is set to "undefined" (infinity); to
 *  suppress this behavior and return any solution, remove every mention of "undef"/"undefined".
 *  Consider using 'long double' and removing the unsolvability check for better stability.
 * Time: O(n^3)
 * Status: tested on kattis:equationsolverplus
 */
#pragma once

#include <cmath>
#include <algorithm>
using namespace std;

typedef vector<double> vd;
const double undefined = 1.0/0.0;
const double eps = 1e-12;
#define A(i,j) A[row[i]][col[j]]
#define B(i) b[row[i]]

int solve_linear2(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), rank = 0;
	vi row(n), col(n), undef(n);
	rep(i,0,n) row[i] = col[i] = i;

	for (int i = 0; i < n; rank = ++i) {
		int br = i, bc = i;
		double v, bv = 0;
		rep(r,i,n) rep(c,i,n)
			if ((v = fabs(A(r,c))) > bv)
				br = r, bc = c, bv = v;
		if (bv <= eps) break;
		bv = A(br,bc);
		swap(row[i], row[br]);
		swap(col[i], col[bc]);
		rep(j,i+1,n) {
			double fac = A(j,i) / bv;
			A(j,i) = 0;
			B(j) -= fac * B(i);
			rep(k,i+1,n) A(j,k) -= fac*A(i,k);
		}
	}

	for (int i = rank; i--; ) {
		B(i) /= A(i,i);
		rep(j,rank,n) {
			if (fabs(A(i,j)) > eps) {
				A(i,j) /= A(i,i);
				undef[i] = true;
			}
			else A(i,j) = 0;
		}
		A(i,i) = 1;
		for (int j = i - 1; j >= 0; --j) {
			double fac = A(j,i);
			A(j,i) = 0;
			B(j) -= fac * B(i);
			rep(k,rank,n) A(j,k) -= fac*A(i,k);
		}
	}

	rep(i,rank,n) if (fabs(B(i)) > eps) return -1;
	rep(i,0,n)
		x[col[i]] = (i >= rank || undef[i] ? undefined : B(i));
	return rank;
}
#undef A
