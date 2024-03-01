#include "../utilities/template.h"

#include "../../content/graph/MaximalCliques.h"

template<class F>
void fastCliques(vector<B>& eds, F f) {
	B R{}, P = ~B(), X{};
	vi deg(sz(eds));
	rep(i,0,sz(eds)) deg[i] = sz(eds[i]);
	rep(j,0,sz(eds)) {
		ll i = (ll)(min_element(all(deg)) - deg.begin());
		R[i] = 1;
		rec(eds, R, P & eds[i], X & eds[i], f);
		R[i] = P[i] = 0; X[i] = 1;
		rep(k,0,sz(eds)) if (eds[i][k]) deg[k]--;
		deg[i] = 1000000;
	}
}

ll main1() {
	rep(n,1,11) rep(m,0,200) {
		vector<B> ed(n);
		rep(i,0,m) {
			ll a = rand() % n, b = rand() % n;
			if (a == b) continue;
			ed[a][b] = 1;
			ed[b][a] = 1;
		}
		unordered_set<B> cl;
		ll co = 0;
		cliques(ed, [&](B x) {
			co++;
			cl.insert(x);
		});
		assert(sz(cl) == co); // no duplicates
		auto isClique = [&](B c) {
			rep(i,0,n) if (c[i])
			rep(j,i+1,n) if (c[j]) {
				if (!ed[i][j]) return false; // not a clique
			}
			rep(i,0,n) if (!c[i]) {
				bool all = true;
				rep(j,0,n) if (c[j]) all &= ed[i][j];
				if (all) return false; // not maximal
			}
			return true;
		};
		for(auto &c: cl) {
			assert(isClique(c));
		}

		ll realCo = 0;
		rep(bi,0,(1 << n)) {
			B c{};
			rep(i,0,n) c[i] = !!(bi & (1 << i));
			if (isClique(c)) realCo++;
		}
		assert(co == realCo);
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}

ll main2() {
	rep(it,0,20) {
		const ll n = 128, m = 4000;
		vector<B> ed(n);
		rep(i,0,m) {
			ll a = rand() % n, b = rand() % n;
			if (a == b) continue;
			ed[a][b] = 1;
			ed[b][a] = 1;
		}
		ll co = 0, sum = 0;
		cliques(ed, [&](B x) { co++; sum += (ll)x.count(); });
		cout << co << ' ' << (double)sum / co << endl;
	}
	return 0;
}

#ifndef target
#define target main1
#endif
int main() { target(); }
