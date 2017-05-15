#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/geometry/PolygonDiameter.h"

int main() {
	srand(2);
	rep(it,0,1000000) {
		int N = rand() % 10;
		vector<Point<ll>> ps;
		rep(i,0,N) {
			ps.emplace_back(rand() % 11 - 5, rand() % 11 - 5);
		}
		ll r1 = 0;
		rep(i,0,N) rep(j,0,i) {
			r1 = max(r1, (ps[i] - ps[j]).dist2());
		}
		pii pa = polygonDiameter(ps);
		ll r2 = ps.empty() ? 0LL : (ps[pa.first] - ps[pa.second]).dist2();
		assert(r1 == r2);
	}
}
