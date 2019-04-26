#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/geometry/ConvexHull.h"
#include "../content/geometry/PointInsideHull.h"
#include "../content/geometry/insidePolygon.h"

int main() {
	rep(it,0,100000) {
		int N = rand() % 15;
		vector<P> ps, ps2;
		rep(i,0,N) ps.emplace_back(rand() % 20 - 10, rand() % 20 - 10);
		trav(i, convexHull(ps)) ps2.push_back(ps[i]);
		if (ps2.empty()) continue;
		rep(it2,0,20) {
			int x = rand() % 22 - 11;
			int y = rand() % 22 - 11;
			P p{x,y};
			assert(insidePolygon(all(ps2), p, true) == (insideHull(ps2, p) == 2));
			assert(insidePolygon(all(ps2), p, false) == (insideHull(ps2, p) >= 1));
		}
	}
}
