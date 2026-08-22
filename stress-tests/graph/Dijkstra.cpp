#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/graph/Dijkstra.h"

int main() {
	rep(it,0,20000) {
		int n = randRange(1, 9);
		int m = randRange(0, 15);
		vector<vector<pii>> graph(n);
		vector<vector<ll>> best(n, vector<ll>(n, INF));
		rep(i,0,n) best[i][i] = 0;
		rep(i,0,m) {
			int u = randRange(n), v = randRange(n);
			int weight = randRange(11);
			graph[u].push_back({v, weight});
			best[u][v] = min(best[u][v], (ll)weight);
		}
		// reference answer: Floyd-Warshall over the same graph
		rep(k,0,n) rep(u,0,n) rep(v,0,n)
			best[u][v] = min(best[u][v], best[u][k] + best[k][v]);

		int start = randRange(n);
		vector<Path> path = dijkstra(graph, start);
		rep(node,0,n) {
			assert(path[node].dist == best[start][node]);
			if (node == start || path[node].dist == INF) {
				assert(path[node].parent == -1);
				continue;
			}
			// the parent must actually lie on a shortest path
			int parent = path[node].parent;
			ll cheapest = INF;
			for (auto [v, weight] : graph[parent])
				if (v == node) cheapest = min(cheapest, (ll)weight);
			assert(path[parent].dist + cheapest == path[node].dist);
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
