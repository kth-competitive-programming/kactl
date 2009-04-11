// Problem: copsrobbers (Kattis)
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

//#include "../../content/geometry/insidePolygon.h"
//#include "../../content/geometry/convexHull.h"
#include "insidePolygon.h"
#include "convexHull.h"

bool solve(int tc) {
	int c,r,o;
	if (!(cin >> c >> r >> o) || !c&&!r&&!o) return false;
	cout << "Data set " << tc+1 << ":" << endl;
	typedef Point<int> P;
	vector<P> C(c),R(r);
	rep(i,0,c) cin >> C[i];
	C.resize(convexHull(C.begin(),C.end())-C.begin());
	rep(i,0,r) cin >> R[i];
	R.resize(convexHull(R.begin(),R.end())-R.begin());
	rep(i,0,o) {
		P p;
		cin >> p;
		if (c>2 && insidePolygon(C.begin(),C.end(),p,false))
			cout << "     Citizen at " << p << " is safe." << endl;
		else if (r>2 && insidePolygon(R.begin(),R.end(),p,false))
			cout << "     Citizen at " << p << " is robbed." << endl;
		else
			cout << "     Citizen at " << p << " is neither." << endl;
	}
	cout << endl;
	return true;
}

int main() {
	int n = 1 << 30;
	if(!n) cin >> n;
	for(int i = 0; i < n && solve(i); ++i);
	return 0;
}
