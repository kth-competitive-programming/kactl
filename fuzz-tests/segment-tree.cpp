#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/data-structures/SegmentTree.h"

static unsigned RA = 1231231;
int ra() {
	RA *= 574841;
	RA += 14;
	return RA >> 1;
}

int main() {
	Tree t(0);
	assert(t.query(0, 0) == t.LOW);

	if (1) {
		const int N = 10000;
		Tree tr(N);
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
		Tree tr(n);
		vi v(n);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % n;

			int r = rand() % 100;
			if (r < 30) {
				int ma = -1234567890;
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
	exit(0);
}
