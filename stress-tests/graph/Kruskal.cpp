#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/graph/Kruskal.h"

// number of connected components spanned by the given edges
int componentCount(int n, const vector<WeightedEdge>& edges) {
	UF components(n);
	int count = n;
	for (const WeightedEdge& edge : edges)
		count -= components.join((int)edge[1], (int)edge[2]);
	return count;
}

int main() {
	rep(it,0,20000) {
		int n = randRange(1, 7);
		int m = randRange(0, 9);
		vector<WeightedEdge> edges;
		rep(i,0,m) {
			int u = randRange(n), v = randRange(n);
			edges.push_back({(ll)randRange(-5, 6), u, v});
		}
		vector<WeightedEdge> tree = kruskal(n, edges);

		// the result must be a forest spanning the same components
		assert(n - sz(tree) == componentCount(n, edges));
		assert(componentCount(n, tree) == componentCount(n, edges));

		ll treeWeight = 0;
		for (const WeightedEdge& edge : tree) treeWeight += edge[0];

		// reference answer: cheapest acyclic subset of the edges
		// that still connects the same components
		ll bestWeight = LLONG_MAX;
		rep(mask,0,1<<m) {
			vector<WeightedEdge> subset;
			ll weight = 0;
			rep(i,0,m) if (mask >> i & 1) {
				subset.push_back(edges[i]);
				weight += edges[i][0];
			}
			if (componentCount(n, subset) != componentCount(n, edges))
				continue;
			// a forest has exactly n - components edges
			if (n - sz(subset) != componentCount(n, subset)) continue;
			bestWeight = min(bestWeight, weight);
		}
		assert(treeWeight == bestWeight);
	}
	cout << "Tests passed!" << endl;
	return 0;
}
