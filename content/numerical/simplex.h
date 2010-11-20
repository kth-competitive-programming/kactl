/**
* Author:
* Date: 2010-11-18
* Source: tinyKACTL
* Description: Solves a linear minimization problem. The first row of the input matrix is the objective function to be minimized. The first column is the maximum allowed value for each linear row.
*/
#pragma once

enum simplex_res { OK, UNBOUNDED, NO_SOLUTION };

template <class M, class I>
simplex_res simplex(M &a, I &var, int m, int n, int twophase=0) {
	while (true) {
	// Choose a variable to enter the basis
		int idx = 0;
		for (int j = 1; j <= n; ++j)
			if (a[0][j] > 0 && (idx == 0 || a[0][j] > a[0][idx]))
			idx = j;
		// Done if all a[m][j]<=0
		if (idx == 0) return OK;
		// Find the variable to leave the basis
		int j = idx; idx = 0;
		for (int i = 1; i <= m; ++i)
			if (a[i][j] > 0 && (idx == 0 || a[i][0]/a[i][j] < a[idx][0]/a[idx][j]))
				idx = i;
		// Problem unbounded if all a[i][j]<=0
		if (idx == 0) return UNBOUNDED;
		// Pivot on a[i][j]
		int i = idx;
		for (int l = 0; l <= n; ++l)
			if (l != j) a[i][l] /= a[i][j];
		a[i][j] = 1;
		for (int k = 0; k <= m + twophase; ++k) if (k != i) {
			for (int l = 0; l <= n; ++l)
				if (l != j) a[k][l] -= a[k][j] * a[i][l];
			a[k][j] = 0;
		}
		// Keep track of the variable change
		var[i] = j;
	}
}
template <class M, class I>
simplex_res twophase_simplex(M &a, I &var, int m, int n, int artificial) {
	// Save primary objective, clear phase I objective
	for (int j = 0; j <= n + artificial; ++j)
		a[m + 1][j] = a[0][j], a[0][j] = 0;
	// Express phase I objective in terms of non-basic variables
	for (int i = 1; i <= m; ++i)
		for (int j = n + 1; j <= n + artificial; ++j)
			if (a[i][j] == 1)
				for (int l = 0; l <= n; ++l)
					if (l != j) a[0][l] += a[i][l];
						simplex(a, var, m, n + artificial, 1); // Simplex phase I
	// Check solution
	for (int j = n + 1; j <= n + artificial; ++j)
		if (a[0][j] >= 0) return NO_SOLUTION;
	// Restore primary objective
	for (int j = 0; j <= n; ++j)
		a[0][j] = a[m + 1][j];
	return simplex(a, var, m, n); // Simplex phase II
}
