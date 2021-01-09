#include "../utilities/template.h"

#include "../../content/graph/PushRelabel.h"
#include "../../content/graph/Dinic.h"
#include "../../content/graph/EdmondsKarp.h"

// Bump allocator, to speed the test up and get rid of malloc performance noise
static char buf[1 << 23];
static size_t bufi = sizeof buf;
void* operator new(size_t s) {
	assert(s < bufi);
	return (void*)&buf[bufi -= s];
}
void operator delete(void*) {}

int main() {
	rep(it,0,500000) {
		bufi = sizeof buf;
		int n = 2 + rand() % 10;
		int s = rand() % n;
		int t = rand() % (n - 1);
		if (t >= s) t++;
		PushRelabel pr(n);
		Dinic dinic(n);
		vector<unordered_map<int, int>> ek(n);

		int m = rand() % 40;
		rep(eit,0,m) {
			int a = rand() % n;
			int b = rand() % n;
			int c = rand() % 4;
			int d = rand() % 4 == 0 ? rand() % 3 + 1 : 0;
			pr.addEdge(a, b, c, d);
			dinic.addEdge(a, b, c, d);
			ek[a][b] += c;
			ek[b][a] += d;
		}
		auto origEk = ek;

		ll flow = pr.calc(s, t);

		// PushRelabel matches Dinic
		ll dinicFlow = dinic.calc(s, t);
		assert(flow == dinicFlow);

		// PushRelabel matches EdmondsKarp
		ll ekFlow = edmondsKarp(ek, s, t);
		assert(flow == ekFlow);

		// Conservation of flow for PushRelabel
		vector<ll> flows(n);
		rep(i,0,n) for(auto &e: pr.g[i]) if (e.f > 0) {
			assert(e.c >= 0);
			flows[i] += e.f;
			flows[e.dest] -= e.f;
		}
		assert(flow == flows[s]);
		assert(flow == -flows[t]);
		rep(i,0,n) if (i != s && i != t) assert(flows[i] == 0);

		// Conservation of flow for Dinic
		vector<ll> dinicFlows(n);
		rep(i,0,n) for(auto &e: dinic.adj[i]) {
			assert(e.flow() <= e.oc);
			dinicFlows[i] += e.flow();
			dinicFlows[e.to] -= e.flow();
		}
		assert(flows == dinicFlows);

		// Conservation of flow for EdmondsKarp
		vector<ll> ekFlows(n);
		rep(i,0,n) for(auto &e: origEk[i]) {
			int nc = ek[i][e.first];
			assert(nc >= 0);
			int flow = e.second - nc;
			if (flow > 0) {
				ekFlows[i] += flow;
				ekFlows[e.first] -= flow;
			}
		}
		assert(flows == ekFlows);

		// PushRelabel computes a cut
		ll acrossCut = 0;
		assert(pr.leftOfMinCut(s));
		assert(!pr.leftOfMinCut(t));
		rep(i,0,n) for(auto &e: pr.g[i]) {
			if (pr.leftOfMinCut(i) && !pr.leftOfMinCut(e.dest)) {
				assert(e.f >= 0);
				assert(e.c == 0);
				acrossCut += e.f;
			}
			if (!pr.leftOfMinCut(i) && pr.leftOfMinCut(e.dest)) {
				assert(e.f <= 0);
			}
		}

		// min cut = max flow
		assert(acrossCut == flow);
	}

	cout << "Tests passed!" << endl;
}
