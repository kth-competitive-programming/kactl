/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * Source: Czech graph algorithms book, by Demel.
 * Description: Finds strongly connected components in a
 * directed graph.
 * Time: O(N + M)
 * Status: works
 * Usage: Create a graph, then run go(graph). As a result
 * you get a number for each vertex - number of SC-component
 * that contains this vertex.
 */
#include <stack>
using namespace std;

vector<int> val, num, comp;
int no_vertices, no_components;
stack<int> z;
template<class G>
void dfs(int j, G &g) {
	val[j] = no_vertices++;
	num[j] = val[j];
	comp[j] = 0;
	z.push(j);
	trav(it,g[j])
		if (comp[*it] == -1) {
			dfs(*it, g);
			num[j] = min(num[j], num[*it]);
		}
		else if (comp[*it] == 0)
			num[j] = min(num[j], val[*it]);
	if (val[j] == num[j]) {
		no_components++;
		while (true) {
			comp[z.top()] = no_components;
			if (z.top() == j) { z.pop(); break; }
			z.pop();
		}
	}
}
template<class G>
vector<int> go(G &g) {
	int n = g.size();
	val.assign(n, 0); num = val;
	no_vertices = no_components = 0;
	comp.assign(n, -1);
	for (int i = 0; i < n; i++) if (comp[i] == -1)
		dfs(i, g);
	for (int i = 0; i < n; i++) comp[i]--;
	return comp;
}
