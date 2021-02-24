#include "../utilities/template.h"

#include "../../content/graph/MaximumClique.h"
namespace maximal {
#include "../../content/graph/MaximalCliques.h"
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
    rep(it, 0, 100000) {
        int n =(rand()%32)+1;
        vb ed(n);
        vector<maximal::B> ed2(n);
        int p =rand()%100;
        rep(i, 0, n) rep(j, 0, i) {
            ed[i][j] = (rand() % 100) < p;
            ed[j][i] = ed[i][j];
            ed2[i][j] = ed[i][j];
            ed2[j][i] = ed[j][i];
        }
        Maxclique clique2(ed);
        int mx = 0;
        maximal::cliques(ed2, [&](auto x){mx = max(mx, int(x.count()));});
        assert(mx == sz(clique2.maxClique()));
    }
    cout<<"Tests passed!"<<endl;
}

