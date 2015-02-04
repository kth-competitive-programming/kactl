/**
* Author:
* Date: 2010-11-18
* Source: tinyKACTL
* Description: Solves a linear minimization problem. The first row of the input matrix is the objective function to be minimized. The first column is the maximum allowed value for each linear row.
*/
#pragma once

enum Result { OK, UNBOUNDED, NO_SOLUTION };

template <class M, class I>
Result simplex(M &a, I &var, int m, int n, int twophase=0) {
	while (true) {
		/// Choose a variable to enter the basis
		int idx = 0;
		rep(j,1,n+1)
			if (a[0][j] > 0 && (!idx || a[0][j] > a[0][idx]))
			idx = j;
		if (!idx) return OK;
		int j = idx; idx = 0;
		rep(i,1,m)
			if (a[i][j] > 0 && (!idx || a[i][0]/a[i][j] < a[idx][0]/a[idx][j]))
				idx = i;
		/// Problem unbounded if all a[m][j] <= 0
		if (!idx) return UNBOUNDED;
		int i = idx;
		for (int l = 0; l <= n; ++l)
			if (l != j) a[i][l] /= a[i][j];
		a[i][j] = 1;
		for (int k = 0; k <= m + twophase; ++k) if (k != i) {
			for (int l = 0; l <= n; ++l)
				if (l != j) a[k][l] -= a[k][j] * a[i][l];
			a[k][j] = 0;
		}
		/// Keep track of the variable change.
		/// XXX this doesn't seem to be used? it is meaningful as output?
		var[i] = j;
	}
}
template <class M, class I>
Result twophase_simplex(M &a, I &var, int m, int n, int artificial) {
	/// Save primary objective, clear phase I objective
	rep(j,0,n+artificial+1)
		a[m + 1][j] = a[0][j], a[0][j] = 0;
	/// Express phase I objective in terms of non-basic variables
	rep(i,1,m+1) rep(j,n+1,n+artificial+1)
			if (a[i][j] == 1)
				rep(l,0,n+1)
					if (l != j) a[0][l] += a[i][l];
	simplex(a, var, m, n + artificial, 1); /// Phase I
	/// Check solution
	rep(j,n+1,n+artificial+1) if (a[0][j] >= 0) return NO_SOLUTION;
	/// Restore primary objective
	rep(j,0,n+1) a[0][j] = a[m + 1][j];
	return simplex(a, var, m, n);
}
