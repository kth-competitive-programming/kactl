#include "../utilities/template.h"

static unsigned RA = 1231231;
int ra() {
	RA *= 574841;
	RA += 14;
	return RA >> 1;
}

namespace maximum {

#include "../../content/data-structures/SegmentTree.h"

}

namespace nonabelian {

// https://en.wikipedia.org/wiki/Dihedral_group_of_order_6
const int lut[6][6] = {
	{0, 1, 2, 3, 4, 5},
	{1, 0, 4, 5, 2, 3},
	{2, 5, 0, 4, 3, 1},
	{3, 4, 5, 0, 1, 2},
	{4, 3, 1, 2, 5, 0},
	{5, 2, 3, 1, 0, 4}
};

struct Tree {
	typedef int T;
	const T unit = 0;
	T f(T a, T b) { return lut[a][b]; }
	vector<T> s; int n;
	Tree(int n = 0, T def = 0) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos > 1; pos /= 2)
			s[pos / 2] = f(s[pos & ~1], s[pos | 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

}

int main() {
	{
		maximum::Tree t(0);
		assert(t.query(0, 0) == t.unit);
	}

	if (0) {
		const int N = 10000;
		maximum::Tree tr(N);
		ll sum = 0;
		rep(it,0,1000000) {
			tr.update(ra() % N, ra());
			int i = ra() % N;
			int j = ra() % N;
			if (i > j) swap(i, j);
			int v = tr.query(i, j+1);
			sum += v;
		}
		cout << sum << endl;
		// return 0;
	}

	rep(n,1,10) {
		maximum::Tree tr(n);
		vi v(n, maximum::Tree::unit);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % (n+2);

			int r = rand() % 100;
			if (r < 30) {
				int ma = tr.unit;
				rep(k,i,j) ma = max(ma, v[k]);
				assert(ma == tr.query(i,j));
			}
			else {
				i = min(i, n-1);
				tr.update(i, x);
				v[i] = x;
			}
		}
	}

	rep(n,1,10) {
		nonabelian::Tree tr(n);
		vi v(n);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % 6;

			int r = rand() % 100;
			if (r < 30) {
				int ma = tr.unit;
				rep(k,i,j) ma = nonabelian::lut[ma][v[k]];
				assert(ma == tr.query(i,j));
			}
			else {
				i = min(i, n-1);
				tr.update(i, x);
				v[i] = x;
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
