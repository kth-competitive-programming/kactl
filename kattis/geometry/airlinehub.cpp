// Problem: airlinehub (Kattis)

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
typedef vector<double> vd;

//#include "../../content/geometry/sphericalDistance.h"
#include "sphericalDistance.h"

bool solve(int tc) {
	int n;
	if (!(cin >> n) || !n) return false;
	vd lon(n), lat(n);
	rep(i,0,n) cin >> lat[i] >> lon[i];
	int bi = 0;
	double bd = 1e100;
	rep(i,0,n) {
		double d = 0;
		rep(j,0,n)
			d = max(d,sphericalDistance(lon[i],lat[i],lon[j],lat[j],1));
		if (d < bd) {
			bd = d;
			bi = i;
		}
	}
	printf("%.2lf %.2lf\n",lat[bi],lon[bi]);
	return true;
}

int main() {
	int n = 1 << 30;
	if(!n) cin >> n;
	for(int i = 0; i < n && solve(i); ++i);
	return 0;
}
