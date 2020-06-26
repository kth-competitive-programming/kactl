#include "../utilities/template.h"

#include "../../content/graph/EulerWalk.h"

struct UF {
	vi v;
	UF(int n) : v(n, -1) {}
	int find(int x) { return v[x] < 0 ? x : v[x] = find(v[x]); }
	void join(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return;
		if (-v[a] < -v[b]) swap(a, b);
		v[a] += v[b];
		v[b] = a;
	}
};

bool hasEulerWalk(vector<vector<pii>>& ed, int start, bool undir, bool cycle) {
	int n = sz(ed);
	int odd = 0;
	bool anyEdges = false;
	vi nins(n);
	rep(i,0,n) {
		for(auto &x: ed[i]) nins[x.first]++;
	}
	rep(i,0,n) {
		if (!ed[i].empty()) anyEdges = true;
		if (undir) {
			assert(sz(ed[i]) == nins[i]);
			int nout = 0;
			for(auto &x: ed[i]) if (x.first != i) nout++;
			if (i != start && nout % 2) odd++;
		}
		else {
			if (nins[i] == sz(ed[i])) continue;
			if (cycle) return false;
			if (abs(nins[i] - sz(ed[i])) > 1) { return false; }
			if (nins[i] < sz(ed[i]) && i != start) { return false; }
		}
	}
	if (odd > !cycle) { return false; }
	if (ed[start].empty() && anyEdges) { return false; }
	UF uf(n);
	rep(i,0,n) for(auto &x: ed[i]) uf.join(i, x.first);
	int comp = 0;
	rep(i,0,n) if (uf.find(i) == i) {
		if (ed[i].empty()) continue;
		comp++;
	}
	return comp <= 1;
}

vi eulerCycle(vector<vector<pii>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges), ret, s = {src};
	// D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
		if (it == end){ ret.push_back(x); s.pop_back(); continue; }
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.push_back(y);
		}}
	for(auto &x: D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}

int main() {
	rep(cycle,0,2) rep(undir,0,2) {
		rep(it,0,10000) {
			int n = rand() % 10 + 1;
			int m = rand() % 20;
			int start = rand() % n;
			vector<vector<pii>> ed(n);
			map<pii, vi> allEds;
			vector<pii> theEdges;
			rep(i,0,m) {
				int a = rand() % n;
				int b = rand() % n;
				ed[a].emplace_back(b, i);
				allEds[pii(a, b)].push_back(i);
				if (undir) {
					ed[b].emplace_back(a, i);
					allEds[pii(b, a)].push_back(i);
				}
				theEdges.emplace_back(a, b);
			}

			vi res = cycle ? eulerCycle(ed, m, start) : eulerWalk(ed, m, start);
			if (0) {
				cout << n << ' ' << m << ' ' << start << ' ' << undir << ' ' << cycle << endl;
				rep(i,0,n) {
					for(auto &x: ed[i]) cout << x.first << ' ';
					cout << endl;
				}
				cout << "returned" << endl;
				for(auto &x: res) cout << x << ' ';
				cout << endl;
				cout << "of length " << sz(res) << endl;
			}

			if (res.empty()) {
				assert(!hasEulerWalk(ed, start, undir, cycle));
			} else {
				assert(hasEulerWalk(ed, start, undir, cycle));

				assert(res[0] == start);
				if (cycle) assert(res.back() == start);
				int cur = start;
				vi seenEdge(m);
				rep(i,1,sz(res)) {
					int x = res[i];
					for(auto &eid: allEds[pii(cur, x)]) {
						if (!seenEdge[eid]) {
							seenEdge[eid] = 1;
							goto ok;
						}
					}
					assert(0); // no usable edge there
ok:
					cur = x;
				}
			}
		}
	}
	cout << "Tests passed!" << endl;
}
