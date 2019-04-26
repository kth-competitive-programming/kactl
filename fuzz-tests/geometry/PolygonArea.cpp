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
#include "../content/geometry/PolygonCenter.h"
#include "../content/geometry/insidePolygon.h"

int main() {
	srand((int)time(0));
	typedef Point<double> P;
	vector<P> ps = {P{0,0}, P{6,4}, P{0,9}};
	int count = 0;
	P su{0,0};
	rep(it,0,10000) {
		double x = rand() / (RAND_MAX + 1.0);
		double y = rand() / (RAND_MAX + 1.0);
		x *= 10;
		y *= 10;
		if (!insidePolygon(all(ps), P{x,y}, true)) continue;
		count++;
		su = su + P{x,y};
	}
	su = su / count;
	double approxArea = (double)count / 10000 * 100;
	cout << polygonArea2(ps)/2.0 << ' ' << approxArea << endl;
	auto p = polygonCenter(ps);
	cout << p.x << ' ' << p.y << ' ' << su.x << ' ' << su.y << endl;
}
