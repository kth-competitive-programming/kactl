#include "../utilities/template.h"

#include "../../content/various/FastKnapsack.h"

int naive(vi w, int t) {
	vector<bool> can_reach(t+1);
	can_reach[0] = true;
	for (int x : w) {
		for (int i = t-x; i >= 0; --i) {
			if (can_reach[i]) can_reach[i+x] = true;
		}
	}
	for (int i = t;; i--)
		if (can_reach[i]) return i;
	assert(false);
}

int main() {
	const int MAX_N = 10;
	const int MAX_W = 10;
	const int iters = 1000000;
	rep(it,0,iters) {
		int n = rand() % MAX_N;
		int maxw = rand() % MAX_W + 1;
		vi w(n);
		rep(i,0,n)
			w[i] = rand()%(maxw+1);
		int t = rand() % (MAX_N*maxw);
		assert(naive(w,t) == knapsack(w,t));
	}
	cout<<"Tests passed!"<<endl;
}
