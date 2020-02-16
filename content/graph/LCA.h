/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Status: Somewhat tested
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected. Can also find the distance between two nodes.
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
	int T = 0;
	vi time, path, ret;
	vector<ll> dist;
	RMQ<int> rmq;

	LCA(graph& C):time(sz(C)), dist(sz(C)), rmq((dfs(C), ret)) {}
	void dfs(graph& C, int v = 0, int p = -1, ll di = 0) {
		time[v] = T++, dist[v] = di;
		trav(e, C[v]) if (e.first != p) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, e.first, v, di + e.second);
		}
	}

	int query(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	ll distance(int a, int b) {
		int lca = query(a, b);
		return dist[a] + dist[b] - 2 * dist[lca];
	}
};
