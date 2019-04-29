/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Unreachable nodes get dist = inf; nodes reachable through negative-weight cycles get dist = -inf.
 * Assumes $VE \cdot \max |w_i| < 2^{63}$.
 * Time: O(EV)
 * Status: Tested on kattis:shortestpath3
 */
#pragma once

const ll inf = LLONG_MAX;
struct Ed { int src, dest, w; };
struct Node { ll dist = inf; int prev = -1; };

void bellmanFord(vector<Node>& nodes, vector<Ed>& eds, int s) {
	nodes[s].dist = 0;

	rep(i,0,sz(nodes)) trav(e, eds) {
		Node cur = nodes[e.src], &dest = nodes[e.dest];
		if (abs(cur.dist) == inf) continue;
		ll d = cur.dist + e.w;
		if (d < dest.dist) {
			dest.prev = e.src;
			dest.dist = (i < sz(nodes)-1 ? d : -inf);
		}
	}
	rep(i,0,sz(nodes)) trav(e, eds) {
		if (nodes[e.src].dist == -inf)
			nodes[e.dest].dist = -inf;
	}
}
