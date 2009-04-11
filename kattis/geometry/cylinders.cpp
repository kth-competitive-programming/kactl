// Problem: cylinders (Kattis)
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

//#include "../../content/geometry/Point.h"
#include "Point.h"

Point<double> next(Point<double> p1, Point<double> p2) {
	double a = acos((p1-p2).dist());
}

bool solve(int tc) {
	int n;
	if (!(cin >> n) || !n) return false;
	vector<Point<double> > v(n);
	rep(i,0,n) cin >> v[i].x;
	sort(v.begin(),v.end());
	while (v.size() > 1) {
		rep(i,0,n-1) 
			v[i] = v[i]+(v[i+1]-v[i]).unit().rotate(acos((v[i]-v[i+1]).dist()/4))*2;
		v.resize(v.size()-1);
	}
	printf("%.4lf %.4lf\n", v[0].x, v[0].y+1);
	return true;
}

int main() {
	int n = 1 << 30;
	if(!n) cin >> n;
	for(int i = 0; i < n && solve(i); ++i);
	return 0;
}
