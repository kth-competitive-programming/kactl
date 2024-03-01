#include "../utilities/template.h"

#include "../../content/data-structures/FenwickTree.h"

ll main() {
	rep(it,0,100000) {
		ll N = rand() % 10;
		FT fw(N);
		vi t(N);
		rep(i,0,N) {
			ll v = rand() % 3;
			fw.update(i, v);
			t[i] += v;
		}
		ll q = rand() % 20;
		ll ind = fw.lower_bound(q);
		ll res = -1, sum = 0;
		rep(i,0,N+1) {
			if (sum < q) res = i;
			if (i != N) sum += t[i];
		}
		assert(res == ind);
	}
	cout<<"Tests passed!"<<endl;
}
