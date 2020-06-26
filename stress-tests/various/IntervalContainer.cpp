#include "../utilities/template.h"

#include "../../content/various/IntervalContainer.h"

int main2() {
	const int its = 4000000;
	set<pii> iv;
	unsigned r = 1;
	rep(it,0,its) {
		r *= 12391231;
		r += 12312;
		int m = (r >> 1) % its;
		addInterval(iv, m, m+1);
	}
	return 0;
}

int main() {
	// return main2();
	const int N = 10;
	const int iters = 10000000;
	set<pii> iv;
	vi line(N);
	ll sum = 0, sumit = 0;
	rep(it,0,iters) {
		int r = rand() % 100;
		if (r < 4) {
			iv.clear();
			line.assign(N, 0);
		}
		else if (r < 60) {
			int l = rand() % (N+1);
			int r = rand() % (N+1);
			if (l > r) swap(l, r);
			addInterval(iv, l, r);
			rep(i,l,r) line[i] = 1;
		}
		else {
			int l = rand() % (N+1);
			int r = rand() % (N+1);
			if (l > r) swap(l, r);
			removeInterval(iv, l, r);
			rep(i,l,r) line[i] = 0;
		}
		int last = -1;
		int ct = 0;
		for(auto &pa: iv) {
			assert(0 <= pa.first && pa.second <= N);
			assert(pa.first < pa.second);
			assert(last < pa.first);
			rep(i,pa.first,pa.second) assert(line[i]);
			last = pa.second;
			ct += pa.second - pa.first;
		}
		rep(i,0,N) ct -= line[i];
		assert(ct == 0);
		sum += sz(iv);
		++sumit;
	}
	cout<<"Tests passed!"<<endl;
}
