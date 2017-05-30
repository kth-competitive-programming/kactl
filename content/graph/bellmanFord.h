/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest path in a graph that might have negative edge distances.
 * Propagates negative infinity distances (sets dist = -inf), and returns true
 * if there is some negative cycle. Unreachable nodes get dist = inf.
 * Time: O(EV)
 * Status: Untested
 */
#pragma once

typedef ll T; // or whatever
struct Edge { int src, dest; T weight; };
struct Node { T dist; int prev; };
struct Graph { vector<Node> nodes; vector<Edge> edges; };

const T inf = numeric_limits<T>::max();
bool bellmanFord2(Graph& g, int start_node) {
	trav(n, g.nodes) { n.dist = inf; n.prev = -1; }
	g.nodes[start_node].dist = 0;

	rep(i,0,sz(g.nodes)) trav(e, g.edges) {
		Node& cur = g.nodes[e.src];
		Node& dest = g.nodes[e.dest];
		if (cur.dist == inf) continue;
		T ndist = cur.dist + (cur.dist == -inf ? 0 : e.weight);
		if (ndist < dest.dist) {
			dest.prev = e.src;
			dest.dist = (i >= sz(g.nodes)-1 ? -inf : ndist);
		}
	}
	bool ret = 0;
	rep(i,0,sz(g.nodes)) trav(e, g.edges) {
		if (g.nodes[e.src].dist == -inf)
			g.nodes[e.dest].dist = -inf, ret = 1;
	}
	return ret;
}
