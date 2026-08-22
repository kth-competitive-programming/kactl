/**
 * Author: Saadan Naqvi
 * Date: 2026-08-23
 * License: CC0
 * Source: folklore
 * Description: Builds a minimum spanning tree by walking the edges from
 * cheapest to most expensive and keeping every edge that joins two nodes
 * not already connected. Each input edge is a \{weight, u, v\} triple, and
 * the chosen edges come back in the order they were taken. A disconnected
 * graph yields a minimum spanning \emph{forest} instead, so the result is a
 * spanning tree exactly when it holds $n-1$ edges. Negate every weight to
 * get a maximum spanning tree.
 * Usage: vector<WeightedEdge> edges = {{5, 0, 1}, {2, 1, 2}};
 *  auto tree = kruskal(n, edges);
 * Time: O(E \log E)
 * Status: Untested
 */
#pragma once
#include "../data-structures/UnionFind.h"

typedef array<ll, 3> WeightedEdge; // {weight, u, v}

vector<WeightedEdge> kruskal(
		int n, vector<WeightedEdge> edges) {
	sort(all(edges)); // cheapest first
	UF components(n);
	vector<WeightedEdge> tree;
	for (WeightedEdge& edge : edges) {
		int u = (int)edge[1], v = (int)edge[2];
		// join() is false when u and v already share a component
		if (components.join(u, v)) tree.push_back(edge);
	}
	return tree;
}
