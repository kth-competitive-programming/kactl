/**
 * Author:
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: N/A
 * Status: Unknown
 */
/* Invert matrix A.  Result is stored in A. */
template <int N>
bool matrix_inverse(double A[N][N], int n) {
	bool singular = false;
	int row[N], col[N];
	double tmp[N][N] ;
	memset(tmp, 0, sizeof(tmp));

	for (int i = 0; i < n; ++i)
		tmp[i][i] = 1, row[i] = col[i] = i;

	for (int i = 0; i < n; ++i) { // forward pass:
		int r = i, c = i; // find pivot
		for (int j = i; j < n; ++j)
			for (int k = i; k < n; ++k)
			if (fabs(A[row[j]][col[k]]) > fabs(A[row[r]][col[c]]))
			r = j, c = k;
		if (fabs(A[row[r]][col[c]]) < 1e-12) // pivot found?
			return false; // if singular
		if (i != r) row[i] ^= row[r] ^= row[i] ^= row[r]; // pivot
		if (i != c) col[i] ^= col[c] ^= col[i] ^= col[c];
		double v = A[row[i]][col[i]]; // eliminate forward
		for (int j = i+1; j < n; ++j) {
			double f = A[row[j]][col[i]] / v;
			A[row[j]][col[i]] = 0;
			for (int k = i+1; k < n; ++k)
				A[row[j]][col[k]] -= f*A[row[i]][col[k]];
			for (int k = 0; k < n; ++k)
				tmp[row[j]][col[k]] -= f*tmp[row[i]][col[k]];
		} // normalize row
		for (int j = i+1; j < n; ++j) A[row[i]][col[j]] /= v;
		for (int j = 0; j < n; ++j)   tmp[row[i]][col[j]] /= v;
		A[row[i]][col[i]] = 1;
	}

	for (int i = n-1; i > 0; --i) // backward pass:
	for (int j = i-1; j >= 0; --j) {
		double v = A[row[j]][col[i]];
	// forget A at this point, just eliminate tmp backward
		for (int k = 0; k < n; ++k)
			tmp[row[j]][col[k]] -= v*tmp[row[i]][col[k]];
	}

	int invcol[n];
	for (int i = 0; i < n; ++i) invcol[col[i]] = i;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		A[i][j] = tmp[row[invcol[i]]][j];
	return true;
}
