/**
 * Author: Unknown, Johan Sannemo
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: Min-cost max-flow
 * Status: Tested
 */
#pragma once
#include <vector>
using namespace std;

typedef int Flow;

struct FlowEdge {
	int dest, back;
	Flow c, f, cost; 
	Flow r() { return c - f; } 
	FlowEdge(int d, int b, Flow c, Flow cost = 0)
		: dest(d), back(b), c(c), f(0), cost(cost) {}
};

template<class G>
void flow_add_edge(G& g, int s, int t,
		Flow c, Flow cost = 0) {
	g[s].push_back(FlowEdge(t, g[t].size(), c, cost));
	g[t].push_back(FlowEdge(s, g[s].size() - 1, 0, cost));
}

Flow inf = 1<<28;

template<class G>
pair<Flow, int> aug(G &g, int s, int t) {
	int n = g.size();
	vector<int> mark(n, -1);
	vector<Flow> mindist(n, inf);
	bool changed = true; mindist[s] = 0;
	for (int i = 1; !(changed = !changed); ++i)
		for (int v = 0; v < n; ++v)
			trav(e, g[v]) {
				Flow dist =mindist[v]+(e.f<0 ? -e.cost : e.cost);
				if (e.r() > 0 && dist < mindist[e.dest]) {
					if (i >= n) assert(0);// negative cycle! shouldn't be
					mindist[e.dest] = dist;
					mark[e.dest] = e.back;
					changed = true;
				}
			}
	if (mark[t] < 0) return make_pair(0, 0);
	Flow inc = inf;
	FlowEdge* e; int v = t;
	while (v != s){
		e = &g[v][mark[v]];
		v = e->dest;
		inc = min(inc, g[v][e->back].r());
	}
	v = t;
	while (v != s)
		e = &g[v][mark[v]], e->f -= inc,
		  v = e->dest, g[v][e->back].f += inc;
	return make_pair(inc, inc * mindist[t]);
}

template<class G>
pair<Flow, int> min_cost_max_flow(G& graph, int s, int t) {
	pair<Flow, int> flow, inc;
	while ((inc = aug(graph, s, t)).first){
		flow.first += inc.first;
		flow.second += inc.second;
	}
	return flow;
}


