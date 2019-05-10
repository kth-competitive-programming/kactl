#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < int(b); ++i)
#define trav(a, v) for (auto &a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/graph/MaximalCliques.h"
#include "../../content/graph/MaximumClique.h"

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
    rep(it, 0, 10000) {
        vector<B> ed(32);
        rep(i, 0, 32) rep(j, 0, i) {
            ed[i][j] = (rand() % 100) < 90;
            ed[j][i] = ed[i][j];
        }
        auto clique2 = new Maxclique(ed);
        int mx = 0;
        cliques(ed, [&](auto x){mx = max(mx, int(x.count()));});
        assert(mx == sz(clique2->maxClique()));
    }
}

