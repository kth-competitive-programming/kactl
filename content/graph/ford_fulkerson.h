/**
* Author:
* Date: 2009-09-25
* Source: tinyKACTL
* Description: DFS and BFS Ford Fulkerson implementations. Min-cost-max-flow returnes the minimal cost for the maximal flow.
* Time: O(E \cdot \# \texttt{ of augumenting paths})
*/
#pragma once

#include "flow_graph.h"
#include <queue>

int mark[MAXNODES];

Flow inc_flow_dfs(adj_list *g, int s, int t, Flow maxf) {
	if (s == t) return maxf;
	Flow inc; mark[s] = 0;
	for (adj_iter it = g[s].begin(); it != g[s].end(); ++it)
	if (mark[it->dest] && it->r() &&
		(inc=inc_flow_dfs(g,it->dest,t,min(maxf, it->r()))))
		return it->f+=inc, g[it->dest][it->back].f -= inc, inc;
	return 0;
}

Flow inc_flow_bfs(adj_list *g, int s, int t, Flow inc) {
	queue<int> q; q.push(s);
	while (!q.empty() && mark[t] < 0) {
		int v = q.front(); q.pop();
		for (adj_iter it = g[v].begin(); it != g[v].end(); ++it)
			if (mark[it->dest] < 0 && it->r())
			mark[it->dest] = it->back, q.push(it->dest);
	}
	if (mark[t] < 0) return 0;
	flow_edge* e; int v = t;
	while (v != s)
		e = &g[v][mark[v]], v = e->dest, inc<?=g[v][e->back].r();
	v = t;
	while (v != s)
		e = &g[v][mark[v]], e->f -= inc,
		v = e->dest, g[v][e->back].f += inc;
	return inc;
}

Flow mindist[MAXNODES], inf = 1<<28;
// For min-cost-max-flow. NB! Needs "cost" field in flow edge!

Flow inc_flow_bellman_ford(adj_list *g, int n, int s, int t) {
	for(int i = 0; i < n; ++i) mindist[i] = inf;
	bool changed = true; mindist[s] = 0;
	for (int i = 1; !(changed = !changed); ++i)
		for (int v = 0; v < n; ++v)
			for (adj_iter it = g[v].begin(); it != g[v].end(); ++it){
				Flow dist =mindist[v]+(it->f<0 ? -it->cost : it->cost);
				if (it->r() > 0 && dist < mindist[it->dest]) {
					if (i >= n) assert(0);// negative cycle! shouldn't be
						mindist[it->dest] = dist;
						mark[it->dest] = it->back;
						changed = true;
				}
			}
	if (mark[t] < 0) return 0;
	Flow inc = inf;
	flow_edge* e; int v = t;
	while (v != s)
		e = &g[v][mark[v]], v = e->dest, inc<?=g[v][e->back].r();
	v = t;
	while (v != s)
		e = &g[v][mark[v]], e->f -= inc,
		v = e->dest, g[v][e->back].f += inc;
	return inc * mindist[t];
}

Flow max_flow(adj_list *graph, int n, int s, int t) {
	Flow flow = 0, inc = 0;
	do flow += inc, memset(mark, 255, sizeof(int)*n);
	while ((inc = inc_flow_dfs(graph, s, t, 1<<28)));
//	while ((inc = inc_flow_bfs(graph, s, t, 1<<28)));
//	while ((inc = inc_flow_bellman_ford(graph, n, s, t)));
	return flow;
}
