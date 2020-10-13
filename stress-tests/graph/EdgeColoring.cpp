#include <random>
#include "../utilities/template.h"

#include "../../content/graph/EdgeColoring.h"

void test(int n, const vector<pii>& ed) {
	vi deg(n);
	for (pii e : ed) ++deg[e.first], ++deg[e.second];
	int maxdeg = n == 0 ? 0 : *max_element(all(deg));
	vi cols = edgeColoring(n, ed);
	assert(sz(cols) == sz(ed));
	vector<vector<bool>> usedCols(n, vector<bool>(maxdeg+1));
	rep(i,0,sz(cols)) {
		int col = cols[i];
		assert(cols[i] <= maxdeg);
		for (int x : {ed[i].first, ed[i].second}) {
			assert(!usedCols[x][col]);
			usedCols[x][col] = 1;
		}
	}
}

vector<pii> randomGraph(int n, int m, mt19937& rng) {
	vector<pii> ed;
	set<pii> seen;
	rep(i,0,m) {
		int a = (int)(rng() % n);
		int b = (int)(rng() % n);
		if (a == b) continue;
		if (!seen.insert(minmax(a, b)).second) continue;
		ed.push_back({a,b});
	}
	return ed;
}

void testCorrect(mt19937& rng) {
	rep(n,0,7) {
		rep(edbits,0,(1 << (n*(n-1)/2))) {
			vector<pii> ed;
			int it = 0;
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
							int ind = __builtin_ctz(bi);
							swap(ed[ind].first, ed[ind].second);
						}
						test(n, ed);
					}
				} while (next_permutation(all(ed)));
			} else {
				int its = n == 5 ? 10 : 5;
				rep(it,0,its) {
					shuffle(all(ed), rng);
					for (auto& e : ed) if (rng() & 128) swap(e.first, e.second);
					test(n, ed);
				}
			}
		}
	}
	rep(n,10,30) rep(it,0,200) {
		int m = (int)(rng() % (n*n));
		vector<pii> ed = randomGraph(n, m, rng);
		test(n, ed);
	}
	for (int n = 1; n <= 1000000; n *= 2) {
		int m = 1000000 / n;
		auto ed = randomGraph(n, m, rng);
		test(n, ed);
	}
	cout << "Tests passed!" << endl;
}

void testPerfRandom(mt19937& rng) {
	rep(i,0,100) {
		int n = 1000;
		int m = 20000;
		auto ed = randomGraph(n, m, rng);
		edgeColoring(n, ed);
	}
}

void testPerfRegular(mt19937& rng) {
	int n = 3000;
	int k = 30;
	// m = 45000
	vector<pii> ed;
	vi cands(n), rem(n, k);
	rep(i,0,n) cands[i] = i;
	int failures = 0;
	set<pii> seen;
	while (!cands.empty()) {
		if (sz(cands) == 1) goto fail;
		int ai = (int)(rng() % sz(cands));
		int bi = (int)(rng() % sz(cands));
		int a = cands[ai], b = cands[bi];
		if (a == b) continue;
		if (!seen.insert(minmax(a, b)).second) {
			if (failures++ > 10) goto fail;
			continue;
		}
		failures = 0;
		ed.push_back({a, b});
		--rem[a], --rem[b];
		if (ai < bi) swap(ai, bi), swap(a, b);
		if (rem[a] == 0) {
			swap(cands[ai], cands.back());
			cands.pop_back();
		}
		if (rem[b] == 0) {
			swap(cands[bi], cands.back());
			cands.pop_back();
		}
	}
	assert(sz(ed) == n * k / 2);
	if (0) {
fail:
		cout << "failed" << endl;
		testPerfRegular(rng);
		return;
	}

	rep(i,0,100) edgeColoring(n, ed);
}

int main(int argc, char** argv) {
	std::mt19937 rng(2);
	string arg = argc == 1 ? "" : argv[1];
	if (arg == "random") testPerfRandom(rng);
	else if (arg == "regular") testPerfRegular(rng);
	else {
		assert(argc == 1);
		testCorrect(rng);
	}
}
