#include "../utilities/template.h"

#include "../../content/various/FastKnapsack.h"

ll naive(vi w, ll t) {
	vector<bool> can_reach(t+1);
	can_reach[0] = true;
	for (ll x : w) {
		for (ll i = t-x; i >= 0; --i) {
			if (can_reach[i]) can_reach[i+x] = true;
		}
	}
	for (ll i = t;; i--)
		if (can_reach[i]) return i;
	assert(false);
}

ll main() {
	const ll MAX_N = 10;
	const ll MAX_W = 10;
	const ll iters = 1000000;
	rep(it,0,iters) {
		ll n = rand() % MAX_N;
		ll maxw = rand() % MAX_W + 1;
		vi w(n);
		rep(i,0,n)
			w[i] = rand()%(maxw+1);
		ll t = rand() % (MAX_N*maxw);
		assert(naive(w,t) == knapsack(w,t));
	}
	cout<<"Tests passed!"<<endl;
}
