/**
 * Author: Per Austrin
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: Solves $A * x = b$, returning either YES, NO, MULT depending on whether there
 *  are 1, 0 or infinitely many solutions.
 *  Data in $A$ and $b$ is lost.
 * Time: O(n^2*m)
 * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
 */
#pragma once

#include <cmath>
#include <algorithm>
using namespace std;

typedef vector<double> vd;
const double eps = 1e-12;
#define A(i,j) A[i][col[j]]

enum { YES, NO, MULT };
int solve_linear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), br = -1, bc = -1;
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		double v, bv = -1;
		rep(r,i,n) rep(c,i,m)
			if ((v = fabs(A(r,c))) > bv)
				br = r, bc = c, bv = v;
		if (bv <= eps) {
			rep(j,i,n) if (fabs(b[j]) > eps) return NO;
			if (i == m) break;
			return MULT;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		bv = 1/A(i,i);
		rep(j,i+1,n) {
			double fac = A(j,i) * bv;
			b[j] -= fac * b[i];
			rep(k,i+1,m) A(j,k) -= fac*A(i,k);
		}
	}
	if (n < m) return MULT;

	for (int i = m; i--;) {
		x[col[i]] = (b[i] /= A(i,i));
		rep(j,0,i)
			b[j] -= A(j,i) * b[i];
	}
	return YES;
}
#undef A
