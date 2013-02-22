/**
 * Author: Chen Xing
 * Date: 2009-04-09
 * Source: http://en.wikipedia.org/wiki/Dijkstra's_algorithm
 * - http://en.wikipedia.org/wiki/Prim's_algorithm
 * - http://en.wikipedia.org/wiki/A-star_algorithm
 * Description: Finds shortest path/minimum spanning tree. Note that none of the shortest path algorithms work with negative edge distances. Consider using bellmanFord or floydWarshall instead. Negative edges are fine for Prim.
 * Time: $O((E + V) \log(V))$ where $E$ is the number of edges and $V$ is the number of vertices, when using default heap-like priority queue.
 * Memory: $O(V)$ where $V$ is the number of vertices.
 * Status: Unknown
 * Usage: typedef Graph<NodeDPAB<double>, EdgeDPAB<double> > G;
 *  G g;
 *  double x = DijkstraPrimAstar<G, Dijkstra>::exec(g, 10, 20);
 */
#pragma once

#include "GraphDPAB.h"
#include <set>
using namespace std;

template<class G, class A, class D = typename G::NodeT::DistanceT, class PQ =
	set<pair<D, int> > > struct DijkstraPrimAstar {
	// Priority queue iterator type.
	typedef PQ::iterator PQIT;

	// Priority queue value type.
	typedef PQ::value_type PQVT; // <distance to source, node>

	static D exec(G& g, int src, int dest = -1) {
		trav(node, g.nodes) {
			node->srcDist = 0;
			node->srcPrev = -1;
		}

		D tot = 0; PQIT pqit; PQ pq;

		g.nodes[src].srcPrev = src;
		pq.insert(PQVT(0, src));
		while(!pq.empty()) {
			int cur = (pqit = pq.begin())->second;
			tot += pqit->first;
			pq.erase(pqit);
			if(cur == dest) break;
			trav(out, g.nodes[cur].outs) {
				int next = out->first;
				D nextDistNew = A::calc<G, D>(g, cur, next, dest, out->second);
				int& nextPrev = g.nodes[next].srcPrev;
				D& nextDist = g.nodes[next].srcDist;
				if(nextPrev == -1 || nextDistNew < nextDist) {
					if((pqit = pq.find(PQVT(nextDist, next))) != pq.end())
						pq.erase(pqit);
					nextPrev = cur;
					nextDist = nextDistNew;
					pq.insert(PQVT(nextDist, next));
				}
			}
		}

		if(dest != -1) return g.nodes[dest].srcDist;
		return tot;
	}
};

struct Dijkstra {
	template<class G, class D>
	static D calc(G& g, int cur, int next, int dest, int edge) {
		return g.nodes[cur].srcDist + g.edges[edge].dist;
	}
};

struct Prim {
	template<class G, class D>
	static D calc(G& g, int cur, int next, int dest, int edge) {
		if(g.nodes[next].srcPrev != -1)
			return g.nodes[next].srcDist;
		return g.edges[edge].dist;
	}
};

struct Astar {
	template<class G, class D>
	static D calc(G& g, int cur, int next, int dest, int edge) {
		return g.nodes[cur].srcDist + g.edges[edge].dist; //# + Heuristic
	}
};
