#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < int(b); ++i)
#define trav(a, v) for (auto &a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/graph/MaximumClique.h"

template<class F>
void cliques(vector<B>& eds, F f, B P = ~B(), B X={}, B R={}) {
	if (!P.any()) { if (!X.any()) f(R); return; }
	auto q = (P | X)._Find_first();
	auto cands = P & ~eds[q];
	rep(i,0,sz(eds)) if (cands[i]) {
		R[i] = 1;
		cliques(eds, f, P & eds[i], X & eds[i], R);
		R[i] = P[i] = 0; X[i] = 1;
	}
}


struct timeit {
	decltype(chrono::high_resolution_clock::now()) begin;
	const string label;
	timeit(string label = "???") : label(label) { begin = chrono::high_resolution_clock::now(); }
	~timeit() {
		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
		cerr << duration << "ms elapsed [" << label << "]" << endl;
	}
};


int main() {
    int n =rand()%32;
    rep(it, 0, 1000000) {
        vector<B> ed(n);
        int p =rand()%100;
        rep(i, 0, n) rep(j, 0, i) {
            ed[i][j] = (rand() % 100) < p;
            ed[j][i] = ed[i][j];
        }
        auto clique2 = new Maxclique(ed);
        int mx = 0;
        cliques(ed, [&](auto x){mx = max(mx, int(x.count()));});
        assert(mx == sz(clique2->maxClique()));
    }
}

