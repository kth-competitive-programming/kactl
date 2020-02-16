/**
 * Author: Johan Sannemo, Simon Lindholm, chilli
 * Date: 2015-09-20
 * License: CC0
 * Source: Folklore
 * Status: Somewhat tested
 * Description: Data structure for computing lowest common
 * ancestors in a tree (with 0 as root). C should be an adjacency list of the tree,
 * either directed or undirected.
 * Can also find the distance between two nodes.
 * Usage:
 *  LCA lca(undirGraph);
 *  lca.query(firstNode, secondNode);
 *  lca.distance(firstNode, secondNode);
 * Time: $O(N \log N + Q)$
 */
#pragma once

typedef vector<pii> vpi;
typedef vector<vpi> graph;

#include "../data-structures/RMQ.h"

struct LCA {
	vi time;
	vector<ll> dist;
	vpi ret;
	int T = 0;
	RMQ<pii> rmq;

	LCA(graph& C) : time(sz(C)),dist(sz(C)),rmq((dfs(C),ret)) {}

	void dfs(graph& C, int v=0, int p=-1, int d=0, ll di=0) {
		if (d) ret.emplace_back(d, p);
		time[v] = T++;
		dist[v] = di;
		trav(e, C[v]) if (e.first != p)
			dfs(C, e.first, v, d + 1, di + e.second);
	}

	int query(int a, int b) {
		if (a == b) return a;
		a = time[a], b = time[b];
		return rmq.query(min(a, b), max(a, b)).second;
	}
	ll distance(int a, int b) {
		int lca = query(a, b);
		return dist[a] + dist[b] - 2 * dist[lca];
	}
};
