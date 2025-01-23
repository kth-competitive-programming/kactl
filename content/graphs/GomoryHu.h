/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2020-04-03
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/graph/gomory_hu_tree.cc#L102
 * Description: Given a list of edges representing an undirected flow graph,
 * returns edges of the Gomory-Hu tree. The max flow between any pair of
 * vertices is given by minimum edge weight along the Gomory-Hu tree path.
 * Time: $O(V)$ Flow Computations
 * Status: Tested on CERC 2015 J, stress-tested
 *
 * Details: The implementation used here is not actually the original
 * Gomory-Hu, but Gusfield's simplified version: "Very simple methods for all
 * pairs network flow analysis". PushRelabel is used here, but any flow
 * implementation that supports `leftOfMinCut` also works.
 */
#pragma once

#include "PushRelabel.h"

typedef array<ll, 3> Edge;
vector<Edge> gomoryHu(int N, vector<Edge> ed) {
	vector<Edge> tree;
	vi par(N);
	rep(i,1,N) {
		PushRelabel D(N); // Dinic also works
		for (Edge t : ed) D.addEdge(t[0], t[1], t[2], t[2]);
		tree.push_back({i, par[i], D.calc(i, par[i])});
		rep(j,i+1,N)
			if (par[j] == par[i] && D.leftOfMinCut(j)) par[j] = i;
	}
	return tree;
}
