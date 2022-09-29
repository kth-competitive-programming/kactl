/**
 * Author: Unknown
 * Source: Unknown
 * License: MIT
 * Description: Solves a general linear maximization problem: maximize $c^T x$ subject to $Ax \le b$, $x \ge 0$.
 * Returns -inf if there is no solution, inf if there are arbitrarily good solutions, or the maximum value of $c^T x$ otherwise.
 * The input vector is set to an optimal $x$ (or in the unbounded case, an arbitrary solution fulfilling the constraints).
 * Numerical stability is not guaranteed. For better performance, define variables such that $x = 0$ is viable.
 * Usage:
 * simplex.init(n, m);
 * simplex.a[i][j] = aij;
 * int val = simplex.solve();
 * Time: O(NM * \#pivots), where a pivot may be e.g. an edge relaxation. O(2^n) in the general case.
 * Status: fixed ig
 */
#pragma once

static constexpr long double eps = 1e-7;
template <class T = double>
struct Simplex {
	int n, m;
	vector<int> l, d;
	vector<vector<T>> a;
	vector<T> b, c, sol;
	T v;

	bool eq(T a, T b) { return fabs(a - b) < eps;  }
	bool ls(T a, T b) { return a < b && !eq(a, b); }

	void init(int p, int q) {
		n = p; m = q; v = 0;
		l.assign(m, 0); b = l;
		d.assign(n, 0); c = sol = d;
		a.assign(m, vector<T>(n, 0));
	}

	void pivot(int x,int y) {
		swap(l[x], d[y]);
		T k = a[x][y]; a[x][y] = 1;
		vector<int> nz;
		rep (i, 0, n) {
				a[x][i] /= k;
				if(!eq(a[x][i], 0)) nz.push_back(i);
		}
		b[x] /= k;
		rep (i, 0, m) {
				if(i == x || eq(a[i][y], 0)) continue;
				k = a[i][y]; a[i][y] = 0;
				b[i] -= k*b[x];
				for(int j : nz) a[i][j] -= k * a[x][j];
		}
		if(eq(c[y], 0)) return;
		k = c[y]; c[y] = 0;
		v += k * b[x];
		for(int i : nz) c[i] -= k * a[x][i];
	}

	// 0: found solution, 1: no feasible solution, 2: unbounded
	int solve() {
		rep (i, 0, n) d[i] = i;
		rep (i, 0, m) l[i] = n+i;
		while(1) { // Eliminating negative b[i]
				int x = -1, y = -1;
				rep (i, 0, m) if (ls(b[i], 0) && (x == -1 || b[i] < b[x])) x = i;
				if(x == -1) break;
				rep (i, 0, n) if (ls(a[x][i], 0) && (y == -1 || a[x][i] < a[x][y])) y = i;
				if(y == -1) return 1;
				pivot(x, y);
		}
		while(1) {
				int x = -1, y = -1;
				rep (i, 0, n)
						if (ls(0, c[i]) && (y == -1 || c[i] > c[y])) y = i;
				if(y == -1) break;
				rep (i, 0, m)
						if (ls(0, a[i][y]) && (x == -1 || b[i]/a[i][y] < b[x]/a[x][y])) x = i;
				if(x == -1) return 2;
				pivot(x, y);
		}
		rep (i, 0, m) if(l[i] < n) sol[l[i]] = b[i];
		return 0;
	}
};
