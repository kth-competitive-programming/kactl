#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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
}
