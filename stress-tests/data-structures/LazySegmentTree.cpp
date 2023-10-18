#include "../utilities/template.h"

#include "../../content/data-structures/LazySegmentTree.h"

static unsigned R;
int ra() {
	R *= 791231;
	R += 1231;
	return (int)(R >> 1);
}
const int inf = 1 << 30;
struct V {
  int v;
  V(int v = -inf) : v(v) {} // must return identity element   
  V operator + (const V& o) const { return V(max(v, o.v)); }
  // merge two Vals, order is important
};
struct T {
  int t;
  T(int t = 0) : t(t) {} // must return identity element
  T operator + (const T& o) const { return T(t + o.t); }
  // compose two Tags, order is important
  V operator() (V v) const { return V(v.v + t); }
  // apply the Tag to v
};

volatile int res;
int main() {
	int N = 10;
	vi v(N);
	iota(all(v), 0);
	random_shuffle(all(v), [](int x) { return ra() % x; });
  vector<V> vs(N);
  rep (i, 0, N) vs[i] = V(v[i]);
	SGT<V, T> tr(vs);
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int ma = -inf;
		rep(k,i,j) ma = max(ma, v[k]);
		assert(ma == tr.query(i,j).v);
	}
	rep(it,0,1000000) {
		int i = ra() % (N+1), j = ra() % (N+1);
		if (i > j) swap(i, j);
		int x = (ra() % 10) - 5;

		int r = ra() % 100;
		if (r < 30) {
			::res = tr.query(i, j).v;
			int ma = -inf;
			rep(k,i,j) ma = max(ma, v[k]);
			assert(ma == ::res);
		}
		else if (r < 70) {
			tr.modify(i, j, T(x));
			rep(k,i,j) v[k] += x;
		}
		else {
      rep(k,i,j) tr.set(k, V(x));
			rep(k,i,j) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
