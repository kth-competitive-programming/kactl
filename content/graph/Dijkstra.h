/**
 * Author: Saadan Naqvi
 * Date: 2026-08-23
 * License: CC0
 * Source: folklore
 * Description: Finds the shortest distance from a start node to every other
 * node, in a graph whose edge weights are all non-negative. The graph is an
 * adjacency list, so \texttt{graph[u]} holds the \{neighbour, weight\} pairs
 * of the edges leaving $u$. For every node you get back its \texttt{dist}
 * from the start (INF if it cannot be reached at all) and its
 * \texttt{parent}, the node just before it on a shortest path
 * ($-1$ for the start node and for unreachable nodes) --
 * following \texttt{parent} repeatedly walks that path backwards.
 * Usage: auto path = dijkstra(graph, start);
 *  ll shortest = path[target].dist;
 * Time: O(E \log V)
 * Status: Untested
 */
#pragma once

const ll INF = LLONG_MAX / 4;
struct Path { ll dist = INF; int parent = -1; };

vector<Path> dijkstra(vector<vector<pii>>& graph, int start) {
	vector<Path> path(sz(graph));
	// max-heap on -distance, so the nearest node pops first
	priority_queue<pair<ll, int>> heap;
	path[start].dist = 0;
	heap.push({0, start});
	while (!heap.empty()) {
		auto [negDist, node] = heap.top(); heap.pop();
		ll dist = -negDist;
		// skip nodes we already settled via a shorter route
		if (dist > path[node].dist) continue;
		for (auto [next, weight] : graph[node])
			if (dist + weight < path[next].dist) {
				path[next] = {dist + weight, node};
				heap.push({-path[next].dist, next});
			}
	}
	return path;
}
