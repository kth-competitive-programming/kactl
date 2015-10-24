/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Status: Works
 * Usage: Create a graph, then run scc(graph). As a result
 * you get a number for each vertex - the index of the component
 * containing that vertex. Components are topologically sorted:
 * they only have edges to components with lower index.
 * no_components will contain the number of connected components.
 */
#include <vector>
using namespace std;

vi orig, low, comp, z;
int no_vertices, no_components;
template<class G> void dfs(int j, G &g) {
	low[j] = orig[j] = no_vertices++;
	comp[j] = -2; z.push_back(j);
	trav(e,g[j])
		if (comp[e] == -1) {
			dfs(e, g);
			low[j] = min(low[j], low[e]);
		}
		else if (comp[e] == -2)
			low[j] = min(low[j], orig[e]);

	if (orig[j] == low[j]) {
		for (;;) {
			int x = z.back(); z.pop_back();
			comp[x] = no_components;
			if (x == j) break;
		}
		no_components++;
	}
}
template<class G> vi scc(G &g) {
	int n = sz(g);
	orig.assign(n, 0); low = orig;
	no_vertices = no_components = 0;
	comp.assign(n, -1);
	rep(i,0,n) if (comp[i] == -1) dfs(i, g);
	return comp;
}
