/**
 * Author: Joshua Andersson
 * Date: 2026-11-21
 * License: CC0
 * Source: San Segundo et al., An exact bit-parallel algorithm for the maximum clique problem (BBMC), 2011
 * Description: Quickly finds a maximum clique of a graph (given as symmetric bitset
 * matrix; self-edges ignored). Can be used to find a maximum independent
 * set by finding a clique of the complement graph.
 * Time: Runs in about 1s for $n \approx 165$ and worst case random graphs (p=.90),
 * 1s for adversarial data at $n \approx 57$. Runs faster for sparse graphs and many structured graphs.
 * Use pragmas for extra speed.
 * Status: stress-tested
 */
typedef bitset<200> B;
typedef vector<B> vb;
vi maxClique(vb g) {
	int n = sz(g); vi deg(n), id(n), q, best; vb e(n); B P;
	rep(i,0,n) deg[i] = g[i].count(), P[i] = 1;
	for (int i = n; i--;) {
		int v = -1;
		rep(u,0,n) if (P[u] && (v < 0 || deg[u] < deg[v])) v = u;
		id[i] = v, P[v] = 0;
		rep(u,0,n) if (g[v][u]) deg[u]--;
	}
	rep(i,0,n) rep(j,0,n) e[i][j] = g[id[i]][id[j]], P[i] = 1;
	auto rec = [&](auto& self, B P) -> void {
		vi ord, col;
		int k = 0, mn = sz(best) - sz(q);
		for (B U = P; U.any(); k++)
			for (B Q = U; Q.any();) {
				int v = Q._Find_first();
				U[v] = Q[v] = 0, Q &= ~e[v];
				if (k >= mn) ord.push_back(v), col.push_back(k + 1);
			}
		for (int i = sz(ord); i--;) {
			if (sz(q) + col[i] <= sz(best)) return;
			int v = ord[i]; q.push_back(v), P[v] = 0;
			self(self, P & e[v]);
			if (sz(q) > sz(best)) best = q;
			q.pop_back();
		}
	};
	rec(rec, P);
	for (int& x : best) x = id[x];
	return best;
}
