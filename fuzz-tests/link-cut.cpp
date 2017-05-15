#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(it, v) for(auto& it : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/graph/LinkCutTree.h"
#include "../content/data-structures/UnionFind.h"

int main() {
	int s = (int)time(0);
	cout << s << endl;
	srand(s);
	for (;;) {
		int N = rand() % 20 + 1;
		rep(it,0,1000) {
			LinkCut lc(N);
			UF uf(N);
			vector<pii> edges;
			rep(it2,0,1000) {
				int v = (rand() >> 4) & 3;
				if (v == 0 && !edges.empty()) { // remove
					int r = (rand() >> 4) % sz(edges);
					pii ed = edges[r];
					swap(edges[r], edges.back());
					edges.pop_back();
					if (rand() & 16)
						lc.cut(ed.first, ed.second);
					else
						lc.cut(ed.second, ed.first);
				} else {
					int a = (rand() >> 4) % N;
					int b = (rand() >> 4) % N;
					uf.e.assign(N, -1);
					trav(ed, edges) uf.join(ed.first, ed.second);
					bool c = uf.same_set(a, b);
					if (!c && v != 1) {
						lc.link(a, b);
						edges.emplace_back(a, b);
					} else {
						assert(lc.connected(a, b) == c);
					}
				}
			}
		}
		clog << '.';
	}
}
