#include "../utilities/template.h"

static unsigned RA = 1231231;
int ra() {
	RA *= 574841;
	RA += 14;
	return RA >> 1;
}

namespace maximum {

int op(int a, int b) { return max(a, b); }
int e() { return INT_MIN; }

#include "../../content/data-structures/SegmentTree.h"

using Tree = SegTree<int, op, e>;

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

int op(int a, int b) { return lut[a][b]; }
int e() { return 0; }

using Tree = maximum::SegTree<int, op, e>;

}

namespace concatenation {

string op(const string& a, const string& b) { return a + b; }
string e() { return {}; }

using Tree = maximum::SegTree<string, op, e>;

}

int main() {
	{
		maximum::Tree t(0);
		assert(t.prod(0, 0) == maximum::e());
	}

	if (0) {
		const int N = 10000;
		maximum::Tree tr(N);
		ll sum = 0;
		rep(it,0,1000000) {
			tr.set(ra() % N, ra());
			int i = ra() % N;
			int j = ra() % N;
			if (i > j) swap(i, j);
			int v = tr.prod(i, j+1);
			sum += v;
		}
		cout << sum << endl;
		// return 0;
	}

	rep(n,1,10) {
		maximum::Tree tr(n);
		vi v(n, maximum::e());
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % (n+2);

			int r = rand() % 100;
			if (r < 30) {
				int ma = maximum::e();
				rep(k,i,j) ma = max(ma, v[k]);
				assert(ma == tr.prod(i,j));
			}
			else {
				i = min(i, n-1);
				tr.set(i, x);
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
				int ma = nonabelian::e();
				rep(k,i,j) ma = nonabelian::lut[ma][v[k]];
				assert(ma == tr.prod(i,j));
			}
			else {
				i = min(i, n-1);
				tr.set(i, x);
				v[i] = x;
			}
		}
	}

	rep(n,1,20) {
		concatenation::Tree tr(n);
		vector<string> v(n);
		rep(i,0,n) {
			v[i] = string(1, char('a' + i));
			tr.set(i, v[i]);
		}
		rep(l,0,n+1) rep(r,l,n+1) {
			string expected;
			rep(i,l,r) expected += v[i];
			assert(tr.prod(l, r) == expected);
		}
	}
	cout<<"Tests passed!"<<endl;
}
