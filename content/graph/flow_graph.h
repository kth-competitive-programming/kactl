/**
 * Author:
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: N/A
 * Status: Unknown
 */
#pragma once
#include <vector>
using namespace std;

typedef int Flow;

struct flow_edge {
  int dest, back;// back is index of back-edge in graph[dest]
  Flow c, f; // capacity and flow
  Flow cost; //used by bellman ford
  Flow r() { return c - f; } // used by ford fulkerson
  flow_edge() {}
  flow_edge(int _dest, int _back, Flow _c, Flow _f = 0
	    /*, Flow _cost = 0*/)
    : dest(_dest), back(_back), c(_c), f(_f)/*, cost(_cost)*/ { }
};

typedef vector<flow_edge> adj_list;
typedef adj_list::iterator adj_iter;

void flow_add_edge(adj_list *g, int s, int t, // add s -> t
		   Flow c, Flow back_c = 0/*, Flow cost = 0*/) {
  g[s].push_back(flow_edge(t, g[t].size(), c/*, 0, cost*/));
  g[t].push_back(flow_edge(s, g[s].size() - 1, back_c
			   /*, 0, cost*/));
}

#define MAXNODES 6000
