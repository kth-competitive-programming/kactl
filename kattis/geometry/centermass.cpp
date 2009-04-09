// Problem: centerofmass (Kattis)
// Author: Ulf Lundström

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
using namespace std;

#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define trav(it, v) for(typeof((v).begin()) it = (v).begin(); \
                        it != (v).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

//#include "../../content/geometry/polygonCenter.h"
//#include "../../content/geometry/convexHull.h"
#include "polygonCenter.h"
#include "convexHull.h"

bool solve(int tc) {
	int n;
	if (!(cin >> n) || n < 3) return false;
	vector<Point<double> > p(n);
	rep(i,0,n) cin >> p[i];
	p.resize(convexHull(p.begin(),p.end())-p.begin());
	Point<double> c = polygonCenter(p.begin(),p.end());
	printf("%.3lf %.3lf\n",c.x,c.y);
	return true;
}

int main() {
	int n = 1 << 30;
	if(!n) cin >> n;
	for(int i = 0; i < n && solve(i); ++i);
	return 0;
}
