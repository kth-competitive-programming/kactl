/**
 * Author: Lukas Polacek
 * Date: 2009-11-01
 * Source: Czech graph algorithms book by Demel.
 * Description: Finds biconnected components in an
 * undirected graph. In a biconnected component there are at least two distinct
 * paths between any two nodes. Note that a vertex can be in more components.
 * Time: $O(N + M)$
 * Status: Tested on UVa Live 4544
 * Usage: Create a graph, then run go(graph). As a result
 * you get a vector with biconnected components.
 */
#include <stack>
#include <vector>
using namespace std;

stack<int> z;
vector<bool> seen;
vector<int> num, v;
int no_vertices;
vector<vector<int> > comp;

template<class G> void dfs(int j, int p, G &g) {
	seen[j] = true;
	num[j] = no_vertices++; v[j] = num[j];
	z.push(j);
	trav(it, g[j]) {
		int i = *it;
		if (!seen[i]) {
			int zz = no_vertices;
			dfs(i, j, g);
			if (v[i] >= num[j]) {
				vector<int> r;
				for (; !z.empty() && num[z.top()] >= zz; z.pop())
					r.push_back(z.top());
				r.push_back(j);
				comp.push_back(r);
			}
			v[j] = min(v[j], v[i]);
		}
		else if (i != p)
			v[j] = min(v[j], num[*it]);
	}
}
template<class G> vector<vector<int> > go(G &g) {
	int n = g.size();
	seen.assign(n, false);
	num.assign(n, 0); v = num;
	no_vertices = 0;
	comp.clear();
	rep(i,0,n)
		if (!seen[i]) dfs(i, -1, g);
	return comp;
}
