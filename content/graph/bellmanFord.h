/**
 * Author: Chen Xing
 * Date: 2009-04-10
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest path in a graph that might have negative edge distances. Returns true if negative-distance cycles exist.
 * Time: O(EV) where $E$ is the number of edges and $V$ is the number of vertices.
 * Memory: O(1)
 * Status: Unknown
 * Usage:
 *  typedef Graph<NodeDPAB<double>, EdgeDPAB<double> > G;
 *  G g;
 *  bool  = bellmanFord(g, 10);
 */
#pragma once

#include "GraphDPAB.h"

template<class G>
bool bellmanFord(G& g, int src) {
	typedef typename G::NodeT N;
	typedef typename N::DistanceT D;

	trav(node, g.nodes) { node.srcDist = 0; node.srcPrev = -1; }
	g.nodes[src].srcPrev = src;
	rep(i, 0, g.nodes.size())
		trav(e, g.edges) {
			int a = e.a, b = e.b;
			rep(j, 0, 1 + e.bidir) {
				N& cur = g.nodes[a];
				if(cur.srcPrev != -1) {
					D nextDistNew = cur.srcDist + e.dist;
					D& nextDist = g.nodes[b].srcDist;
					int& nextPrev = g.nodes[b].srcPrev;
					if(nextPrev == -1 || nextDistNew < nextDist) {
						if(i == (g.nodes.size() - 1)) return true;
						nextPrev = a;
						nextDist = nextDistNew;
					}
				}
				swap(a, b);
			}
		}
	return false;
}
