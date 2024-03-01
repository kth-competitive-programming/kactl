#include "../utilities/template.h"

// #include "mcmf3.h"
// #include "mcmf4.h"
// #include "mcmfold.h"
// #include "mcmfnew.h"
#include <bits/extc++.h>
#define setpi dummy(){} bool setpi
#undef assert
#define assert(x) return x
#include "../../content/graph/MinCostMaxFlow.h"
#undef assert
#undef setpi
#include <cassert>
#include "MinCostMaxFlow2.h"

struct MCMF2 {
	vector<vector<FlowEdge>> g;
	MCMF2(ll n) : g(n) {}
	void addEdge(ll s, ll t, Flow c, Flow cost = 0) {
		flow_add_edge(g, s, t, c, cost);
	}
	pair<ll, ll> maxflow(ll s, ll t) {
		return min_cost_max_flow(g, s, t);
	}
	void setpi(ll s) {}
};

// typedef MCMF2 MCMF;

#if 1
static size_t i;
#else
static char buf[450 << 20];
static size_t i = sizeof buf;
void* operator new(size_t s) {
	assert(s < i);
	return (void*)&buf[i -= s];
}
void operator delete(void*) noexcept {}
#endif

typedef vector<ll> vd;
bool zero(ll x) { return x == 0; }
ll MinCostMatching(const vector<vd>& cost, vi& L, vi& R) {
	ll n = sz(cost), mated = 0;
	vd dist(n), u(n), v(n);
	vi dad(n), seen(n);

	/// construct dual feasible solution
	rep(i,0,n) {
		u[i] = cost[i][0];
		rep(j,1,n) u[i] = min(u[i], cost[i][j]);
	}
	rep(j,0,n) {
		v[j] = cost[0][j] - u[0];
		rep(i,1,n) v[j] = min(v[j], cost[i][j] - u[i]);
	}

	/// find primal solution satisfying complementary slackness
	L = vi(n, -1);
	R = vi(n, -1);
	rep(i,0,n) rep(j,0,n) {
		if (R[j] != -1) continue;
		if (zero(cost[i][j] - u[i] - v[j])) {
			L[i] = j;
			R[j] = i;
			mated++;
			break;
		}
	}

	for (; mated < n; mated++) { // until solution is feasible
		ll s = 0;
		while (L[s] != -1) s++;
		fill(all(dad), -1);
		fill(all(seen), 0);
		rep(k,0,n)
			dist[k] = cost[s][k] - u[s] - v[k];

		ll j = 0;
		for (;;) { /// find closest
			j = -1;
			rep(k,0,n){
				if (seen[k]) continue;
				if (j == -1 || dist[k] < dist[j]) j = k;
			}
			seen[j] = 1;
			ll i = R[j];
			if (i == -1) break;
			rep(k,0,n) { /// relax neighbors
				if (seen[k]) continue;
				auto new_dist = dist[j] + cost[i][k] - u[i] - v[k];
				if (dist[k] > new_dist) {
					dist[k] = new_dist;
					dad[k] = j;
				}
			}
		}

		/// update dual variables
		rep(k,0,n) {
			if (k == j || !seen[k]) continue;
			auto w = dist[k] - dist[j];
			v[k] += w, u[R[k]] -= w;
		}
		u[s] += dist[j];

		/// augment along path
		while (dad[j] >= 0) {
			ll d = dad[j];
			R[j] = R[d];
			L[R[j]] = j;
			j = d;
		}
		R[j] = s;
		L[s] = j;
	}

	auto value = vd(1)[0];
	rep(i,0,n) value += cost[i][L[i]];
	return value;
}

void testPerf() {
	srand(2);
	ll N = 500, E = 10000, CAPS = 100, COSTS = 100000;
	MCMF mcmf(N);
	ll s = 0, t = 1;
	rep(i,0,E) {
		ll a = rand() % N;
		ll b = rand() % N;
		ll cap = rand() % CAPS;
		ll cost = rand() % COSTS;
		if (a == b) continue;
		mcmf.addEdge(a, b, cap, cost);
		// ::cap[a][b] = cap;
		// ::cost[a][b] = cost;
	}
	auto pa = mcmf.maxflow(s, t);
	cout << pa.first << ' ' << pa.second << endl;
}

void testMatching() {
	rep(it,0,100000) {
		size_t last = ::i;
		ll N = rand() % 10, M = rand() % 10;
		ll NM = max(N, M);
		vector<vd> co(NM, vd(NM));
		rep(i,0,N) rep(j,0,M) co[i][j] = (rand() % 10) + 2;
		vi L, R;
		ll v = MinCostMatching(co, L, R);
		ll S = N+M, T = N+M+1;
		MCMF mcmf(N+M+2);
		rep(i,0,N) mcmf.addEdge(S, i, 1, 0);
		rep(i,0,M) mcmf.addEdge(N+i, T, 1, 0);
		rep(i,0,N) rep(j,0,M) mcmf.addEdge(i, N+j, 1, co[i][j] - 2);
		mcmf.setpi(S);
		auto pa = mcmf.maxflow(S, T);
		assert(pa.first == min(N, M));
		assert(pa.second == v - 2 * pa.first);
		::i = last;
	}
}

void testNeg() {
	const ll ITS = 1000000;
	ll ed[100][100];
	ll negs = 0;
	rep(it,0,ITS) {
		size_t lasti = ::i;
		ll N = rand() % 7 + 2;
		ll M = rand() % 17;
		ll S = 0, T = 1;
		MCMF mcmf(N);
		MCMF2 mcmf2(N);
		rep(i,0,N) rep(j,0,N) ed[i][j] = 0;
		bool anyneg = false;
		rep(eid,0,M) {
			ll i = rand() % N, j = rand() % N;
			if (i != j && !ed[i][j]) {
				ed[i][j] = 1;
				ll fl = rand() % 50;
				ll co = rand() % 11 - 3;
				mcmf.addEdge(i, j, fl, co);
				mcmf2.addEdge(i, j, fl, co);
				if (co < 0) anyneg = true;
			}
		}
		negs += anyneg;
		if (anyneg || rand() % 3 == 0) {
			if (!mcmf.setpi(S))  // has negative loops
				continue;
		}
		auto pa = mcmf.maxflow(S, T);
		auto pa2 = mcmf2.maxflow(S, T);
		assert(pa == pa2);
		::i = lasti;
	}
	// cerr << negs << "/" << ITS << " graphs with negative edge costs" << endl;
	cout<<"Tests passed!"<<endl;
}

int main() {
	testMatching();
	testNeg();
}
