// Problem: wrapping
// Author: Ulf Lundstrom

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

//#include "../../content/geometry/convexHull.h"
//#include "../../content/geometry/polygonArea.h"
#include "convexHull.h"
#include "polygonArea.h"

bool solve(int tc) {
	typedef Point<double> P;
	int n;
	if (!(cin >> n) || !n) return false;
	vector<Point<double> > p;
	double A = 0;
	rep(k,0,n) {
		double x,y,w,h,v;
		cin >> x >> y >> w >> h >> v;
		A += w*h;
		for (int i=-1; i < 2; i+=2) for (int j=-1; j < 2; j+=2)
			p.push_back(P(x,y)+P(w*i,h*j).rotate(-v*M_PI/180)/2);
	}
	p.resize(convexHull(p.begin(),p.end())-p.begin());
	double f = A/(polygonArea2<double>(p.begin(),p.end())/2);
	//cout << A << polygonArea2<double>(p.begin(),p.end())/2 << endl;
	printf("%.1lf %%\n",100*f);
	return true;
}

int main() {
	int n = 0;
	if(!n) cin >> n;
	for(int i = 0; i < n && solve(i); ++i);
	return 0;
}
