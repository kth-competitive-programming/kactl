#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/geometry/MinimumEnclosingCircle.h"

int main() {
	srand(2);
	rep(it,0,1000000) {
		int N = rand() % 20 + 1;
		// int N = 4;
		vector<P> ps;
		rep(i,0,N) {
			ps.emplace_back(rand() % 21 - 10, rand() % 21 - 10);
		}

		pair<double, P> pa = enclosingCircle(ps);
		double rad = pa.first;
		P mid = pa.second;
		double maxDist = 0;
		trav(p, ps) {
			maxDist = max(maxDist, (p - mid).dist());
		}

		assert(abs(maxDist - rad) < 1e-6);

		rep(it2,0,50) {
			P q2 = mid - P(0, 1e-6).rotate(it2);
			trav(p, ps) {
				if((p - q2).dist() > rad - 1e-7) goto fail;
			}
			assert(0);
fail:;
		}
	}
}
