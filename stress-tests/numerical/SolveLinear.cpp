#include "../utilities/template.h"

const int mod = 3;
const int nmax = 4, mmax = 4, nmmax = 10;

const int lut[9] = {-4,-2,-3,-1,-100,1,3,2,4};

int modinv(int x) {
	assert(x);
	return x;
	// return lut[x+4];
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
void rec(int i, int j, vector<vd>& A, F f) {
	if (i == sz(A)) {
		f();
	}
	else if (j == sz(A[i])) {
		rec(i+1, 0, A, f);
	}
	else {
		rep(v,0,mod) {
			A[i][j] = v;
			rec(i, j+1, A, f);
		}
	}
}

template<class F>
void rec2(int i, vd& A, F f) {
	if (i == sz(A)) f();
	else {
		rep(v,0,mod) {
			A[i] = v;
			rec2(i+1, A, f);
		}
	}
}

int main() {
	rep(n,0,nmax+1) rep(m,0,mmax+1) {
		int nm = n*m;
		if (nm > nmmax) continue;
		vector<vd> A(n, vd(m));
		vd b(n), x(m), theX(m);
		rec(0, 0, A, [&]() {
			rec2(0, b, [&]() {
				int sols = 0;
				rec2(0, x, [&]() {
					rep(i,0,n) {
						int v = 0;
						rep(j,0,m) v += A[i][j] * x[j];
						if (v % mod != b[i]) return;
					}
					sols++;
					if (sols == 1) theX = x;
				});
				vector<vd> A2 = A;
				vd x2 = x, b2 = b;
				int r = solveLinear(A2, b2, x2);
				if (sols == 0) assert(r == -1);
				else if (sols == 1) assert(r == m);
				else assert(r < m);
				if (sols == 1) assert(x2 == theX);
			});
		});
	}
	cout<<"Tests passed!"<<endl;
}
