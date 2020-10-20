#pragma once
#include "random.h"

vector<pii> randomSimpleGraphAsEdgeList(int n, int m) {
	assert(m <= (ll)n * (n - 1) / 2);
	vector<pii> ed;
	if (m > (ll)n * n / 3) {
		rep(i,0,n) rep(j,0,i) {
			int a = i, b = j;
			if (randBool()) swap(a, b);
			ed.push_back({a,b});
		}
		shuffle_vec(ed);
		ed.erase(ed.begin() + m, ed.end());
	} else {
		set<pii> seen;
		rep(i,0,m) {
			int a = randRange(n);
			int b = randRange(n);
			if (a == b) continue;
			if (!seen.insert(minmax(a, b)).second) continue;
			ed.push_back({a,b});
		}
	}
	return ed;
}

vector<vi> randomSimpleGraph(int n, int m) {
	vector<vi> ed(n);
	for (auto pa : randomSimpleGraphAsEdgeList(n, m)) {
		ed[pa.first].push_back(pa.second);
		ed[pa.second].push_back(pa.first);
	}
	for (auto& v : ed) shuffle_vec(v);
	return ed;
}

vector<pii> randomRegularGraphAsEdgeList(int n, int k) {
	// TODO: this is slow and requires a lot of retries for large n, change to
	// something smarter.
	assert(k < n);
	vector<pii> ed;
	vi cands(n), rem(n, k);
	rep(i,0,n) cands[i] = i;
	int failures = 0;
	set<pii> seen;
	while (!cands.empty()) {
		if (sz(cands) == 1) goto fail;
		int ai = randRange(sz(cands));
		int bi = randRange(sz(cands));
		int a = cands[ai], b = cands[bi];
		if (a == b) continue;
		if (!seen.insert(minmax(a, b)).second) {
			if (failures++ > 100) goto fail;
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
	return ed;
fail:
	cerr << "retry" << endl;
	return randomRegularGraphAsEdgeList(n, k);
}
