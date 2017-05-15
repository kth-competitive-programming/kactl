#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/graph/2sat.h"

/*
int main3() {
	const int N = 100000, M = 10000000;
	{
		TwoSat ts(N);
		rep(i,0,M) {
			int r = rand();
			int s = r;
			r >>= 2;
			int a = r % N;
			r >>= 5;
			int b = r % N;
			if (a == b) continue;
			ts.either(a, s&1, b, s&2);
		}
		cout << ts.solve() << endl;
	}
	{
		vector<bool> v(N);
		rep(i,0,N) v[i] = rand() & (1 << 20);
		TwoSat ts(N);
		rep(i,0,M) {
			int r = rand();
			int s = r;
			r >>= 2;
			int a = r % N;
			r >>= 5;
			int b = r % N;
			if (a == b) continue;
			ts.either(a, v[a], b, s&1);
		}
		cout << ts.solve() << endl;
	}
	return 0;
}

int main2() {
	int N = 4;
	TwoSat ts(N);
	ts.either(0,1,1,1);
	ts.either(0,1,1,0);
	ts.either(2,0,3,0);
	cout << ts.solve() << endl;
	rep(i,0,4) cout << ts.values[i] << ' '; cout << endl;
	return 0;
}
*/

int ra() {
	static unsigned X;
	X *= 1283611;
	X += 123;
	return X >> 1;
}

int main() {
	const int N = 100, M = 400;
	rep(it,0,100) {
		vector<bool> v(N);
		rep(i,0,N) v[i] = ra() & (1 << 20);
		TwoSat ts(N);
		vi r;
		rep(i,0,M) {
			if (ra()%100 < 5) {
				int r = ra();
				int s = r;
				r >>= 2;
				int a = r % N;
				r >>= 5;
				int b = r % N;
				if (a == b) continue;
				ts.either(v[a] ? a : ~a, (s&1) ? b : ~b);
			} else {
				int k = ra() % 4 + 1;
				r.clear();
				rep(ki,0,k-1) {
					int a = ra() % N;
					r.push_back(v[a] ? ~a : a);
				}
				r.push_back(ra() % (2*N) - N);
				random_shuffle(all(r), [](int x) { return ra() % x; });
				ts.at_most_one(r);
			}
		}
		assert(ts.solve());
		int to = 0;
		rep(i,0,N) to += (ts.values[i] == v[i]);
		cout << to << '/' << N << endl;
	}
}
