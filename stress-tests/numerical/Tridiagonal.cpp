#include "../utilities/template.h"

namespace finite_field {

const int mod = 7;
// const int inv[] = {0, 1, 3, 2, 4};
const int inv[] = {0, 1, 4, 5, 2, 3, 6};
struct T {
	int x;
	T() : x(0) {}
	T(int y) : x(y % mod) { if (x < 0) x += mod; }
};
T operator+(T a, T b) { return {a.x + b.x}; }
T operator-(T a, T b) { return {a.x - b.x}; }
T operator*(T a, T b) { return {a.x * b.x}; }
T operator/(T a, T b) { assert(b.x); return {a.x * inv[b.x]}; }
T& operator+=(T& a, T b) { return a = a + b; }
T& operator-=(T& a, T b) { return a = a - b; }
T& operator*=(T& a, T b) { return a = a * b; }
T& operator/=(T& a, T b) { return a = a / b; }

vector<T> tridiagonal(vector<T> diag, const vector<T>& super,
		const vector<T>& sub, vector<T> b) {
	int n = sz(b); vi tr(n);
	rep(i,0,n-1) {
		if (diag[i].x == 0) {
			if (super[i].x == 0) return {};
			if (sub[i].x == 0) return {};
			b[i+1] -= b[i] * diag[i+1] / super[i];
			if (i+2 < n) b[i+2] -= b[i] * sub[i+1] / super[i];
			diag[i+1] = sub[i]; tr[++i] = 1;
		} else {
			diag[i+1] -= super[i]*sub[i]/diag[i];
			b[i+1] -= b[i]*sub[i]/diag[i];
		}
	}
	if (diag[n-1].x == 0) return {};
	for (int i = n; i--;) {
		if (tr[i]) {
			swap(b[i], b[i-1]);
			diag[i-1] = diag[i];
			b[i] /= super[i-1];
		} else {
			b[i] /= diag[i];
			if (i) b[i-1] -= b[i]*super[i-1];
		}
	}
	return b;
}

int modinv(int x) {
	assert(x);
	if (x < 0) x += mod;
	return inv[x];
}

typedef vector<int> vd;

int solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		int v, bv = -1;
		rep(r,i,n) rep(c,i,m)
			if ((v = A[r][c])) {
				br = r, bc = c, bv = v;
				goto found;
			}
		rep(j,i,n) if (b[j]) return -1;
		break;
found:
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = modinv(A[i][i]);
		rep(j,i+1,n) {
			int fac = A[j][i] * bv % mod;
			b[j] = (b[j] - fac * b[i]) % mod;
			rep(k,i+1,m) A[j][k] = (A[j][k] - fac*A[i][k]) % mod;
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] = ((b[i] * modinv(A[i][i]) % mod) + mod) % mod;
		x[col[i]] = b[i];
		rep(j,0,i)
			b[j] = (b[j] - A[j][i] * b[i]);
	}
	return rank;
}

template<class F>
void rec(T& b, int& a, F f) {
	rep(i,0,mod) a = i, b = T(i), f();
}

int main() {
#ifdef BRUTEFORCE
	const int n = 3;
	vector<vi> mat(n, vi(n)), mat2;
	vi b(n), b3, x(n);
	vector<T> b2(n);
	vector<T> diag(n);
	vector<T> super(n-1);
	vector<T> sub(n-1);
	rec(diag[0], mat[0][0], [&]() {
	rec(diag[1], mat[1][1], [&]() {
	rec(diag[2], mat[2][2], [&]() {
	rec(super[0], mat[0][1], [&]() {
	rec(super[1], mat[1][2], [&]() {
	rec(sub[0], mat[1][0], [&]() {
	rec(sub[1], mat[2][1], [&]() {
	rec(b2[0], b[0], [&]() {
	rec(b2[1], b[1], [&]() {
	rec(b2[2], b[2], [&]() {
#else
	rep(it,0,1000000) {
	const int n = 1 + rand() % 10;
	vector<vi> mat(n, vi(n)), mat2;
	vi b(n), b3, x(n);
	vector<T> b2(n);
	vector<T> diag(n);
	vector<T> super(n-1);
	vector<T> sub(n-1);
	rep(i,0,n) {
		diag[i] = T(mat[i][i] = rand() % mod);
		b2[i] = T(b[i] = rand() % mod);
	}
	rep(i,0,n-1) {
		super[i] = T(mat[i][i+1] = rand() % mod);
		sub[i] = T(mat[i+1][i] = rand() % mod);
	}
#endif
		mat2 = mat;
		b3 = b;
		int r = solveLinear(mat2, b3, x);
		auto x2 = tridiagonal(diag, super, sub, b2);
		if (r != n) {
			assert(x2.empty());
		} else {
			rep(i,0,n) if (x2[i].x != (x[i] + mod) % mod) {
				goto fail;
			}
			if (false) {
fail:;
				rep(i,0,n) {
					rep(j,0,n) cout << mat[i][j] << ' ';
					cout << "x = " << b[i];

					cout << "  " << x[i] << "  " << x2[i].x << endl;
				}
				abort();
			}
		}
#ifdef BRUTEFORCE
	});
	});
	});
	});
	});
	});
	});
	});
	});
	});
#else
	}
#endif
	return 0;
}

}

namespace real {

typedef double T;
vector<T> tridiagonal(vector<T> diag, const vector<T>& super,
		const vector<T>& sub, vector<T> b) {
	int n = sz(b); vi tr(n);
	rep(i,0,n-1) {
		if (abs(diag[i]) < 1e-9 * abs(super[i])) { // diag[i] == 0
			throw false; // assert that this doesn't happen; we're testing stability
			b[i+1] -= b[i] * diag[i+1] / super[i];
			if (i+2 < n) b[i+2] -= b[i] * sub[i+1] / super[i];
			diag[i+1] = sub[i]; tr[++i] = 1;
		} else {
			diag[i+1] -= super[i]*sub[i]/diag[i];
			b[i+1] -= b[i]*sub[i]/diag[i];
		}
	}
	for (int i = n; i--;) {
		if (tr[i]) {
			swap(b[i], b[i-1]);
			diag[i-1] = diag[i];
			b[i] /= super[i-1];
		} else {
			b[i] /= diag[i];
			if (i) b[i-1] -= b[i]*super[i-1];
		}
	}
	return b;
}

typedef double T;
typedef vector<double> vd;

int solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		double v, bv = -1;
		rep(r,i,n) rep(c,i,m)
			if ((v = A[r][c])) {
				br = r, bc = c, bv = v;
				goto found;
			}
		rep(j,i,n) if (b[j]) return -1;
		break;
found:
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
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] /= A[i][i];
		x[col[i]] = b[i];
		rep(j,0,i)
			b[j] = (b[j] - A[j][i] * b[i]);
	}
	return rank;
}

int positiveDefinite(vector<vd>& A) {
	int n = sz(A), m = n;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		double v = A[i][i];
		if (v < 1e-9) return false;
		double bv = 1/A[i][i];
		rep(j,i+1,n) {
			double fac = A[j][i] * bv;
			rep(k,i+1,m) A[j][k] -= fac*A[i][k];
		}
	}
	return true;
}

double bf_nice_doubles[] = {-1, 0, 1, 0.5, -0.5, 1/3.0, 2};
double nice_doubles[] = {-1, 0, 0, 1, 0.5, -0.5, 1/3.0, -1/3.0, 2, -2};
double nice_double() {
	return nice_doubles[rand() % (sizeof nice_doubles / sizeof *nice_doubles)];
}

bool validMat(const vector<vd>& mat) {
	const int n = sz(mat);
	bool faila = false, failb = false, sym = true;
	rep(i,0,n) {
		double suma = 0, sumb = 0;
		rep(j,0,n) {
			if (mat[i][j] != mat[j][i]) sym = false;
			suma += abs(mat[i][j]);
			sumb += abs(mat[j][i]);
		}
		if (!suma || suma / 2 >= abs(mat[i][i])) faila = true;
		if (!sumb || sumb / 2 >= abs(mat[i][i])) failb = true;
	}
	if (!faila || !failb) return true;
	if (sym) {
		vector<vd> mat2 = mat;
		return positiveDefinite(mat2);
	}
	return false;
}

template<class F>
void rec(T& a, T& b, F f) {
	for (double x : bf_nice_doubles) {
		b = a = x;
		f();
	}
}

int main() {
	ll count = 0;
#ifdef BRUTEFORCE
	const int n = 3;
	vector<vd> mat(n, vd(n)), mat2;
	vd b(n), b3, x(n), x2(n);
	vector<T> b2(n);
	vector<T> diag(n);
	vector<T> super(n-1);
	vector<T> sub(n-1);
	rec(diag[0], mat[0][0], [&]() {
	rec(diag[1], mat[1][1], [&]() {
	rec(diag[2], mat[2][2], [&]() {
	rec(super[0], mat[0][1], [&]() {
	rec(super[1], mat[1][2], [&]() {
	rec(sub[0], mat[1][0], [&]() {
	rec(sub[1], mat[2][1], [&]() {
	rec(b2[0], b[0], [&]() {
	rec(b2[1], b[1], [&]() {
	rec(b2[2], b[2], [&]() {
#else
	rep(it,0,10000000) {
	const int n = 1 + rand() % 10;
	vector<vd> mat(n, vd(n)), mat2;
	vd b(n), b3, x(n), x2(n);
	vector<T> b2(n);
	vector<T> diag(n);
	vector<T> super(n-1);
	vector<T> sub(n-1);
	rep(i,0,n) {
		diag[i] = mat[i][i] = nice_double();
		b2[i] = b[i] = nice_double();
	}
	bool sym = rand() % 3 == 0;
	rep(i,0,n-1) {
		double x = nice_double();
		super[i] = mat[i][i+1] = x;
		double y = sym ? x : nice_double();
		sub[i] = mat[i+1][i] = y;
	}
#endif
	{
		if (!validMat(mat)) goto skip;
		count++;
		mat2 = mat;
		b3 = b;
		bool done = false;
		try {
			int r = solveLinear(mat2, b3, x);
			x2 = tridiagonal(diag, super, sub, b2);
			assert(r == n);
			done = true;
			rep(i,0,n) if (abs(x2[i] - x[i]) > 1e-6) {
				throw false;
			}
		} catch (bool) {
			rep(i,0,n) {
				rep(j,0,n) cout << mat[i][j] << ' ';
				cout << "x = " << b[i];

				cout << "  " << x[i] << "  ";
				if (done) cout << x2[i];
				else cout << "?";
				cout << endl;
			}
			abort();
		}
	} skip:;
#ifdef BRUTEFORCE
	});
	});
	});
	});
	});
	});
	});
	});
	});
	});
#else
	}
#endif
	cout<<"Tests passed!"<<endl;
	return 0;
}

}

int main() {
	// finite_field::main();
	real::main();
}
