#include "../utilities/template.h"

#include "../../content/number-theory/FracBinarySearch.h"

int main() {
	rep(n,1,300) {
		vector<pair<double, pii>> v;
		rep(i,0,n+1) rep(j,1,n+1) if (__gcd(i,j) == 1) {
			double r = (double)i / j;
			v.emplace_back(r, pii(i,j));
		}
		v.emplace_back(1e9, pii(0,0));
		sort(all(v));
		map<double, pii> actual(all(v));

		rep(iter,0,100000) {
			double x = rand() / (RAND_MAX + 1.0);
			// x *= min(n, 10); // if testing with search range (0, n)
			auto fn = [&](Frac f) { return (double)f.p >= x * (double)f.q; };
			Frac f = fracBS(fn, n);
			auto best = actual.lower_bound(x)->second;
			assert(best.first == f.p);
			assert(best.second == f.q);
		}
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}
