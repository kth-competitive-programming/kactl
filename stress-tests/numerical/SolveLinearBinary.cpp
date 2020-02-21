#include "../utilities/template.h"

const int nmax = 5, mmax = 5, nmmax = 16;

typedef bitset<5> bs;

int solveLinear(vector<bs>& A, vi& b, bs& x, int m) {
	int n = sz(A), rank = 0, br;
	assert(m <= sz(x));
	vi col(m); iota(all(col), 0);
	rep(i,0,n) {
		for (br=i; br<n; ++br) if (A[br].any()) break;
		if (br == n) {
			rep(j,i,n) if(b[j]) return -1;
			break;
		}
		int bc = (int)A[br]._Find_next(i-1);
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) if (A[j][i] != A[j][bc]) {
			A[j].flip(i); A[j].flip(bc);
		}
		rep(j,i+1,n) if (A[j][i]) {
			b[j] ^= b[i];
			A[j] ^= A[i];
		}
		rank++;
	}

	x = bs();
	for (int i = rank; i--;) {
		if (!b[i]) continue;
		x[col[i]] = 1;
		rep(j,0,i) b[j] ^= A[j][i];
	}
	return rank; // (multiple solutions if rank < m)
}

template<class F>
void rec(int i, int j, vector<bs>& A, int m, F f) {
	if (i == sz(A)) {
		f();
	}
	else if (j == m) {
		rec(i+1, 0, A, m, f);
	}
	else {
		rep(v,0,2) {
			A[i][j] = v;
			rec(i, j+1, A, m, f);
		}
	}
}

template<class F>
void rec2(int i, bs& A, int m, F f) {
	if (i == m) f();
	else {
		rep(v,0,2) {
			A[i] = v;
			rec2(i+1, A, m, f);
		}
	}
}

int main() {
	int ct = 0;
	rep(n,0,nmax+1) rep(m,0,mmax+1) {
		int nm = n*m;
		if (nm > nmmax) continue;
		vector<bs> A(n, bs(m));
		bs b, x, theX;
		vi b2(n);
		rec(0, 0, A, m, [&]() {
			rec2(0, b, n, [&]() {
				int sols = 0;
				rec2(0, x, m, [&]() {
					rep(i,0,n) {
						int v = 0;
						rep(j,0,m) v ^= A[i][j] & x[j];
						if (v != b[i]) return;
					}
					sols++;
					if (sols == 1) theX = x;
				});
				vector<bs> A2 = A;
				bs x2 = x; rep(i,0,n) b2[i] = b[i];
				int r = solveLinear(A2, b2, x2, m);
				if (sols == 0) assert(r == -1);
				else if (sols == 1) assert(r == m);
				else assert(r < m);
				if (sols == 1) assert(x2 == theX);
				ct++;
			});
		});
	}
	cout<<"Tests passed!"<<endl;
}
