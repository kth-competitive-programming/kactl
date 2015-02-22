/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * Source: Czech graph algorithms book, by Demel.
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V) where $E$ is the number of edges and $V$ is the number of vertices.
 * Status: Works
 * Usage: Create a graph, then run go(graph). As a result
 * you get a number for each vertex - a number of SC-component
 * containing this vertex.
 */
#include <stack>
using namespace std;

vector<int> val, num, comp;
int no_vertices, no_components;
stack<int> z;
template<class G> void dfs(int j, G &g) {
	num[j] = val[j] = no_vertices++; comp[j] = 0; z.push(j);
	trav(e,g[j])
		if (comp[e] == -1) {
			dfs(e, g);
			num[j] = min(num[j], num[e]);
		}
		else if (comp[e] == 0)
			num[j] = min(num[j], val[e]);

	if (val[j] == num[j]) {
		no_components++;
		while (true) {
			comp[z.top()] = no_components;
			if (z.top() == j) { z.pop(); break; }
			z.pop();
		}
	}
}
template<class G> vector<int> go(G &g) {
	int n = g.size();
	val.assign(n, 0); num = val;
	no_vertices = no_components = 0;
	comp.assign(n, -1);
	rep(i,0,n) if (comp[i] == -1) dfs(i, g);
	rep(i,0,n) comp[i]--;
	return comp;
}
