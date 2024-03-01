#include "../utilities/template.h"

#include "../../content/data-structures/RMQ.h"

ll main() {
	srand(2);
	rep(N,0,100) {
		vi v(N);
		rep(i,0,N) v[i] = i;
		random_shuffle(all(v));
		RMQ<ll> rmq(v);
		rep(i,0,N) rep(j,i+1,N+1) {
			ll m = rmq.query(i,j);
			ll n = 1 << 29;
			rep(k,i,j) n = min(n, v[k]);
			assert(n == m);
		}
	}
	cout<<"Tests passed!"<<endl;
}
