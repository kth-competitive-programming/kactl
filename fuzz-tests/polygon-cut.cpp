#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/geometry/PolygonArea.h"
#include "../content/geometry/polygonCut.h"
#include "../content/geometry/sideOf.h"
#include "../content/geometry/insidePolygon.h"
#include "../content/geometry/SegmentIntersection.h"

typedef Point<double> P;
int main() {
	rep(it,0,500) {
		int N = rand() % 10 + 3;
		vector<P> ps;
		rep(i,0,N) ps.emplace_back(rand() % 10 - 5, rand() % 10 - 5);
		P p(rand() % 10 - 5), q(rand() % 10 - 5);
		rep(i,0,N) rep(j,i+1,N) {
			P a = ps[i], b = ps[(i+1)%N];
			P c = ps[j], d = ps[(j+1)%N];
			P r1, r2;
			int r = segmentIntersection(a, b, c, d, r1, r2);
			if (r == 2) goto fail;
			if (r == 1) {
				if (i+1 == j || (j+1) % N == i) ;
				else goto fail;
			}
		}
		if (p == q) { fail: continue; }

		int count = 0;
		const int ITS = 400000;
		rep(it,0,ITS) {
			double x = rand() / (RAND_MAX + 1.0) * 10 - 5;
			double y = rand() / (RAND_MAX + 1.0) * 10 - 5;
			if (!insidePolygon(all(ps), P{x,y}, true)) continue;
			if (sideOf(p, q, P{x,y}) > 0) continue;
			count++;
		}
		double approxArea = (double)count / ITS * 100;

		ps = polygonCut(ps, p, q);
		double realArea = ps.empty() ? 0.0 : abs(polygonArea2(ps) / 2.0);

		cout << setprecision(2) << fixed;
		cout << N << ' ' << realArea << '\t' << approxArea << '\t' << realArea - approxArea << endl;

		// cerr << N << endl;
		// trav(x, ps) {
			// cout << x.x << ' ' << x.y << endl;
		// }
	}
}
