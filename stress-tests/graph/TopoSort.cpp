#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/graph/TopoSort.h"

ll main() {
	rep(it,0,50000) {
		ll n = rand() % 20;
		ll m = n ? rand() % 30 : 0;
		bool acyclic = randBool();
		vi order(n);
		iota(all(order), 0);
		shuffle_vec(order);
		vector<vi> ed(n);
		rep(i,0,m) {
			ll a = rand() % n;
			ll b = rand() % n;
			if (acyclic && a >= b) continue;
			ed[order[a]].push_back(order[b]);
		}
		vi ret = topoSort(ed);
		if (acyclic) assert(sz(ret) == n);
		else assert(sz(ret) <= n);
		vi seen(n);
		for (ll i : ret) {
			assert(!seen[i]++);
			for (ll j : ed[i])
				assert(!seen[j]);
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
