#include "../utilities/template.h"

typedef vector<double> vd;
const double eps = 1e-12;

enum { YES, NO, MULT };
int solve_linear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), br = -1, bc = -1;
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		double v, bv = -1;
		rep(r,i,n) rep(c,i,m)
			if ((v = fabs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv <= eps) {
			rep(j,i,n) if (fabs(b[j]) > eps) return NO;
			if (i == m) break;
			return MULT;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = 1/A[i][i];
		rep(j,i+1,n) {
			double fac = A[j][i] * bv;
			b[j] -= fac * b[i];
			rep(k,i+1,m) A[j][k] -= fac*A[i][k];
		}
	}
	if (n < m) return MULT;

	for (int i = m; i--;) {
		x[col[i]] = (b[i] /= A[i][i]);
		rep(j,0,i)
			b[j] -= A[j][i] * b[i];
	}
	return YES;
}

int main() {
	const int n = 1000;
	vector<vd> A(n, vd(n));
	rep(i,0,n) rep(j,0,n) A[i][j] = rand() * 1000.0 / RAND_MAX;
	vd x(n), b(n);
	rep(i,0,n) b[i] = rand() * 1000.0 / RAND_MAX;
	int r = solve_linear(A, b, x);
	assert(r == 0);
	cout<<"Tests passed!"<<endl;
	// cout << r << endl;
	// rep(i,0,n) cout << x[i] << ' ';
	// cout << endl;
}
