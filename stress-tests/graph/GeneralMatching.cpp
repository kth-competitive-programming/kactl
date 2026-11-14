#include "../utilities/template.h"

#include "../../content/graph/GeneralMatching.h"

// Maximum matching by DP over subsets of matched vertices.
int bruteMatching(int N, const vector<pii>& ed) {
	vi dp(1 << N);
	rep(m,0,1 << N) for (pii e : ed) {
		int b = 1 << e.first | 1 << e.second;
		if (!(m & b)) dp[m | b] = max(dp[m | b], dp[m] + 1);
	}
	return *max_element(all(dp));
}

int main() {
	mt19937 rng(17);
	rep(it,0,200'000) {
		int N = rng() % 10 + 1;
		int E = rng() % (N * (N - 1) / 2 + 1);
		set<pii> eds;
		rep(i,0,E) {
			int a = rng() % N, b = rng() % N;
			if (a == b) continue;
			if (a > b) swap(a, b);
			eds.insert({a, b});
		}
		vector<pii> ed(all(eds));
		for (pii& e : ed) if (rng() % 2) swap(e.first, e.second);

		vector<pii> res = generalMatching(N, ed);
		vi used(N);
		for (pii e : res) {
			assert(eds.count(minmax(e.first, e.second)));
			assert(!used[e.first]++ && !used[e.second]++);
		}
		assert(sz(res) == bruteMatching(N, ed));
	}
	cout<<"Tests passed!"<<endl;
}
