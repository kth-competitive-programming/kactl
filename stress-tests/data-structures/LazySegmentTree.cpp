#include "../utilities/template.h"

#include "../../content/data-structures/LazySegmentTree.h"

static unsigned R;
ll ra() {
	R *= 791231;
	R += 1231;
	return (ll)(R >> 1);
}

volatile ll res;
int main() {
	ll N = 10;
	vi v(N);
	iota(all(v), 0);
	random_shuffle(all(v), [](ll x) { return ra() % x; });
	Node* tr = new Node(v,0,N);
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		ll ma = -inf;
		rep(k,i,j) ma = max(ma, v[k]);
		assert(ma == tr->query(i,j));
	}
	rep(it,0,1000000) {
		ll i = ra() % (N+1), j = ra() % (N+1);
		if (i > j) swap(i, j);
		ll x = (ra() % 10) - 5;

		ll r = ra() % 100;
		if (r < 30) {
			::res = tr->query(i, j);
			ll ma = -inf;
			rep(k,i,j) ma = max(ma, v[k]);
			assert(ma == ::res);
		}
		else if (r < 70) {
			tr->add(i, j, x);
			rep(k,i,j) v[k] += x;
		}
		else {
			tr->set(i, j, x);
			rep(k,i,j) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
