#include "../utilities/template.h"

#include "../../content/graph/LinkCutTree.h"
#include "../../content/data-structures/UnionFind.h"

int main() {
	srand(2);
	LinkCut lczero(0);
	rep(it,0,10000) {
		ll N = rand() % 20 + 1;
		LinkCut lc(N);
		UF uf(N);
		vector<pii> edges;
		rep(it2,0,1000) {
			ll v = (rand() >> 4) & 3;
			if (v == 0 && !edges.empty()) { // remove
				ll r = (rand() >> 4) % sz(edges);
				pii ed = edges[r];
				swap(edges[r], edges.back());
				edges.pop_back();
				if (rand() & 16)
					lc.cut(ed.first, ed.second);
				else
					lc.cut(ed.second, ed.first);
			} else {
				ll a = (rand() >> 4) % N;
				ll b = (rand() >> 4) % N;
				uf.e.assign(N, -1);
				for(auto &ed: edges) uf.join(ed.first, ed.second);
				bool c = uf.sameSet(a, b);
				if (!c && v != 1) {
					lc.link(a, b);
					edges.emplace_back(a, b);
				} else {
					assert(lc.connected(a, b) == c);
				}
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
