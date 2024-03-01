#include <random>
#include "../utilities/template.h"
#include "../utilities/genGraph.h"
#include "../utilities/random.h"

#include "../../content/graph/EdgeColoring.h"

void test(ll n, const vector<pii>& ed) {
	vi deg(n);
	for (pii e : ed) ++deg[e.first], ++deg[e.second];
	ll maxdeg = n == 0 ? 0 : *max_element(all(deg));
	vi cols = edgeColoring(n, ed);
	assert(sz(cols) == sz(ed));
	vector<vector<bool>> usedCols(n, vector<bool>(maxdeg+1));
	rep(i,0,sz(cols)) {
		ll col = cols[i];
		assert(cols[i] <= maxdeg);
		for (ll x : {ed[i].first, ed[i].second}) {
			assert(!usedCols[x][col]);
			usedCols[x][col] = 1;
		}
	}
}

void testCorrect() {
	rep(n,0,7) {
		rep(edbits,0,(1 << (n*(n-1)/2))) {
			vector<pii> ed;
			ll it = 0;
			rep(i,0,n) rep(j,i+1,n) {
				if (edbits & 1 << (it++)) {
					ed.push_back({i, j});
				}
			}
			if (n <= 4 || n + sz(ed) <= 9) {
				// test all k!*2^k input orders
				sort(all(ed));
				if (n != 0) do {
					rep(bi,0,(1 << sz(ed))) {
						if (bi) {
							ll ind = __builtin_ctz(bi);
							swap(ed[ind].first, ed[ind].second);
						}
						test(n, ed);
					}
				} while (next_permutation(all(ed)));
			} else {
				ll its = n == 5 ? 10 : 5;
				rep(it,0,its) {
					shuffle_vec(ed);
					for (auto& e : ed) if (randBool()) swap(e.first, e.second);
					test(n, ed);
				}
			}
		}
	}
	rep(n,10,30) rep(it,0,200) {
		ll m = randIncl(n * (n-1) / 2);
		vector<pii> ed = randomSimpleGraphAsEdgeList(n, m);
		test(n, ed);
	}
	for (ll n = 1; n <= 1000000; n *= 2) {
		ll m = (ll) min(1000000LL / n, (ll)n * (n-1) / 2);
		auto ed = randomSimpleGraphAsEdgeList(n, m);
		test(n, ed);
	}
	cout << "Tests passed!" << endl;
}

void testPerfRandom() {
	rep(i,0,100) {
		ll n = 1000;
		ll m = 20000;
		auto ed = randomSimpleGraphAsEdgeList(n, m);
		edgeColoring(n, ed);
	}
}

void testPerfRegular() {
	ll n = 3000;
	ll k = 30;
	// m = 45000
	vector<pii> ed = randomRegularGraphAsEdgeList(n, k);
	rep(i,0,100) edgeColoring(n, ed);
}

ll main(ll argc, char** argv) {
	srand(2);
	string arg = argc == 1 ? "" : argv[1];
	if (arg == "random") testPerfRandom();
	else if (arg == "regular") testPerfRegular();
	else {
		assert(argc == 1);
		testCorrect();
	}
}
