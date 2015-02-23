/**
 * Author: Chen Xing
 * Date: 2009-04-10
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest path in a graph that might have negative edge distances. Returns true if negative-distance cycles exist.
 * Time: O(EV)
 * Status: Unknown
 * Usage:
 *  typedef Graph<NodeDPAB<int>, EdgeDPAB<int> > G;
 *  G g; bool negCyc = bellmanFord(g, 10);
 */
#pragma once

#include "GraphDPAB.h"

template<class G>
bool bellmanFord(G& g, int src) {
	trav(node, g.nodes) { node.srcDist = 0; node.srcPrev = -1; }
	g.nodes[src].srcPrev = src;
	rep(i, 0, g.nodes.size()) trav(e, g.edges) {
		int a = e.a, b = e.b;
		rep(j, 0, 1 + e.bidir) {
			auto& cur = g.nodes[a];
			if(cur.srcPrev != -1) {
				auto nextDistNew = cur.srcDist + e.dist;
				auto& nextDist = g.nodes[b].srcDist;
				int& nextPrev = g.nodes[b].srcPrev;
				if(nextPrev == -1 || nextDistNew < nextDist) {
					if(i == sz(g.nodes) - 1) return true;
					nextPrev = a;
					nextDist = nextDistNew;
				}
			}
			swap(a, b);
		}
	}
	return false;
}
