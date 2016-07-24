/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * Source: Wikipedia
 * Description: Given an undirected graph, finds all the edges whose removal
 * would increase the number of connected components.
 * Time: O(V + E)
 * Status: lightly tested on CodeForces
 */

struct Node {
	int lo, epar, time = 0;
	vector<pii> ed;
};
vector<Node> nodes;
int nedges = 0;

void add_edge(int a, int b) {
	nodes[a].ed.emplace_back(b, nedges);
	nodes[b].ed.emplace_back(a, nedges++);
	// (and add to some edge container and return nedges, say)
}

void dfs(Node& n, int epar, int& time) {
	n.epar = epar; n.lo = n.time = ++time;
	trav(e, n.ed) if (e.second != epar) {
		Node& o = nodes[e.first];
		n.lo = min(n.lo, o.time ?: (dfs(o, e.second, time), o.lo));
	}
}

vector<bool> find_bridges() {
	int time = 0;
	trav(n, nodes) if (!n.time) dfs(n, -1, time);
	vector<bool> ret(nedges);
	trav(n, nodes)
		if (n.lo == n.time && n.epar != -1) ret[n.epar] = 1;
	return ret;
}
