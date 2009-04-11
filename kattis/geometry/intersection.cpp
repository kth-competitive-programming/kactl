// Problem: intersection (Kattis)
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

//#include "../../content/geometry/segmentIntersection.h"
//#include "../../content/geometry/insidePolygon.h"
#include "segmentIntersection.h"
#include "insidePolygon.h"

bool solve(int tc) {
	typedef Point<ll> P;
	Point<ll> s,e,c1,c2,d1,d2;
	cin >> s >> e >> c1 >> c2;
	P p[4] = {c1,P(c1.x,c2.y),c2,P(c2.x,c1.y)};
	bool res = segmentIntersection(s,e,c1,P(c1.x,c2.y),d1,d2) ||
			segmentIntersection(s,e,c1,P(c2.x,c1.y),d1,d2) ||
			segmentIntersection(s,e,c2,P(c2.x,c1.y),d1,d2) ||
			segmentIntersection(s,e,c2,P(c1.x,c2.y),d1,d2) ||
			insidePolygon(p,p+4,s,false);
	cout << (res?"T":"F") << endl;
	return true;
}

int main() {
	int n = 0;
	if(!n) cin >> n;
	for(int i = 0; i < n && solve(i); ++i);
	return 0;
}
