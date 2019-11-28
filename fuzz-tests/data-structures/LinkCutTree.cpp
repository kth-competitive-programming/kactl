#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(it, v) for(auto& it : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/graph/LCT.h"
#include "../../content/data-structures/UnionFind.h"

bool dfs(vi &path, bitset<20> &vis, vector<set<int>> &g, int a, int &b) {
	path.push_back(a);
	vis[a] = 1;
	if(a == b) return true;
	trav(u, g[a]) if(!vis[u]) if (dfs(path, vis, g, u, b)) return true;
	path.pop_back();
	return false;
}

int main() {
	srand(2);
	LinkCut lczero(0);
	rep(it,0,10000) {
		int N = rand() % 20 + 1;
		LinkCut lc(N);
		UF uf(N);
		vector<pii> edges;
		vector<set<int>> g(N);
		vector<int> val(N);
		bitset<20> vis;
		queue<int> q;
		vi cc;
		vi path;
		rep(it2,0,1000) {
			int v = (rand() >> 4) & 7;
			if (v == 0 && !edges.empty()) { // remove
				int r = (rand() >> 4) % sz(edges);
				pii ed = edges[r];
				swap(edges[r], edges.back());
				edges.pop_back();
				g[ed.first].erase(ed.second);
				g[ed.second].erase(ed.first);
				if (rand() & 16)
					lc.cut(ed.first, ed.second);
				else
					lc.cut(ed.second, ed.first);
			} else if(v & 1) {
				int a = (rand() >> 4) % N;
				int b = (rand() >> 4) % N;
				uf.e.assign(N, -1);
				trav(ed, edges) uf.join(ed.first, ed.second);
				bool c = uf.same_set(a, b);
				if (!c && v != 1) {
					lc.link(a, b);
					edges.emplace_back(a, b);
					g[a].emplace(b); g[b].emplace(a);
				} else {
					assert(lc.isConnected(a, b) == c);
				}
			} else if (v & 2) {
				int a = (rand() >> 4) % N;
				int b = rand() % 10000;
				val[a] += b;
				lc.update(a, b);
			} else {
				int a = (rand() >> 4) % N;
				vis.reset(), queue<int>().swap(q), vi().swap(cc);
				q.push(a);
				while(sz(q)) {
					int u = q.front(); q.pop();
					vis[u] = 1;
					cc.push_back(u);
					trav(e, g[u]) if(!vis[e]) q.push(e);
				}
				int r = (rand() >> 4) % sz(cc);
				int b = cc[r];
				vis.reset();
				vi().swap(path);
				assert(dfs(path, vis, g, a, b));
				int mx = 0;
				trav(x, path) mx = max(mx, val[x]);
				assert(lc.query(a, b) == mx);
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
