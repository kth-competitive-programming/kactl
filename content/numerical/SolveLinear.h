/**
 * Author: Per Austrin
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: Solves $A * x = b$, returning either YES, NO, MULT depending on whether there
 *  are 1, 0 or infinitely many solutions.
 *  Data in $A$ and $b$ is lost.
 * Time: O(n^3)
 * Status: tested on kattis:equationsolver
 */
#pragma once

#include <cmath>
#include <algorithm>
using namespace std;

typedef vector<double> vd;
const double eps = 1e-12;
#define A(i,j) A[row[i]][col[j]]
#define B(i) b[row[i]]

enum { YES, NO, MULT };
int solve_linear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A);
	vi row(n), col(n);
	rep(i,0,n) row[i] = col[i] = i;

	rep(i,0,n) {
		int br = i, bc = i;
		double v, bv = -1;
		rep(r,i,n) rep(c,i,n)
			if ((v = fabs(A(r,c))) > bv)
				br = r, bc = c, bv = v;
		if (bv < eps) {
			rep(j,i,n) if (fabs(B(j)) > eps) return NO;
			return MULT;
		}
		bv = A(br,bc);
		swap(row[i], row[br]);
		swap(col[i], col[bc]);
		rep(j,i+1,n) {
			double fac = A(j,i) / bv;
			B(j) -= fac * B(i);
			rep(k,i+1,n) A(j,k) -= fac*A(i,k);
		}
	}

	for (int i = n-1; i >= 0; --i) {
		B(i) /= A(i,i);
		rep(j,0,i)
			B(j) -= A(j,i) * B(i);
	}
	rep(i,0,n) x[col[i]] = B(i);
	return YES;
}
#undef A
