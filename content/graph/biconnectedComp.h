/**
 * Author: Lukas Polacek
 * Date: 2009-11-01
 * Source: Czech graph algorithms book by Demel.
 * Description: Finds biconnected components in an
 * undirected graph. In a biconnected component there are at least two distinct
 * paths between any two nodes. Note that a node can be in several components.
 * Time: O(E + V) where $E$ is the number of edges and $V$ is the number of vertices.
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

template<class G> void dfs(int at, int p, G &g) {
	seen[at] = true;
	num[at] = no_vertices++; v[at] = num[at];
	z.push(at);
	trav(i, g[at]) {
		if (!seen[i]) {
			int zz = no_vertices;
			dfs(i, at, g);
			if (v[i] >= num[at]) {
				vector<int> r;
				for (; !z.empty() && num[z.top()] >= zz; z.pop())
					r.push_back(z.top());
				r.push_back(at);
				comp.push_back(r);
			}
			v[at] = min(v[at], v[i]);
		}
		else if (i != p)
			v[at] = min(v[at], num[i]);
	}
}
template<class G> vector<vector<int> > go(G &g) {
	int n = sz(g);
	seen.assign(n, false);
	num.assign(n, 0); v = num;
	no_vertices = 0;
	comp.clear();
	rep(i,0,n)
		if (!seen[i]) dfs(i, -1, g);
	return comp;
}
