/**
 * Author: Per Austrin
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: N/A
 * Status: Unknown
 */
const double undefined = 1.0/0.0;
const double eps = 1e-12;

// Solves A*x = b, or as much of x as possible. Returns rank.
// Data in A and b is lost.
template <int N> int
solve_linear(int n, double A[N][N], double b[N], double x[N]) {
	int row[N], col[N], undef[N], invrow[N], invcol[N], rank = 0;
	for (int i = 0; i < n; ++i)
		row[i] = col[i] = i, undef[i] = false;

	for (int i = 0; i < n; rank = ++i) {
		int br = i, bc = i;
		double v, bv = abs(A[row[i]][col[i]]);
		for (int r = i; r < n; ++r)
			for (int c = i; c < n; ++c)
				if ((v = abs(A[row[r]][col[c]])) > bv)
					br = r, bc = c, bv = v;
		if (bv < eps) break;
		if (i != br) row[i] ^= row[br] ^= row[i] ^= row[br];
		if (i != bc) col[i] ^= col[bc] ^= col[i] ^= col[bc];
		for (int j = i + 1; j < n; ++j) {
			double fac = A[row[j]][col[i]] / bv;
			A[row[j]][col[i]] = 0;
			b[row[j]] -= fac * b[row[i]];
			for (int k = i + 1; k < n; ++k)
				A[row[j]][col[k]] -= fac * A[row[i]][col[k]];
		}
	}

	for (int i = rank; i-- ; ) {
		b[row[i]] /= A[row[i]][col[i]];
		A[row[i]][col[i]] = 1;
		for (int j = rank; j < n; ++j)
			if (abs(A[row[i]][col[j]]) > eps)
				undef[i] = true;
		for (int j = i - 1; j >= 0; --j) {
			if (undef[i] && abs(A[row[j]][col[i]]) > eps)
				undef[j] = true;
			else {
				b[row[j]] -= A[row[j]][col[i]] * b[row[i]];
				A[row[j]][col[i]] = 0;
			}
		}
	}

	for (int i = 0; i < n; ++i)
		invrow[row[i]] = i, invcol[col[i]] = i;
	for (int i = 0; i < n; ++i)
		if (invrow[i] >= rank || undef[invrow[i]]) b[i] = undefined;
	for (int i = 0; i < n; ++i) x[i] = b[row[invcol[i]]];
	return rank;
}
