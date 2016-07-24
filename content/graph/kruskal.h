/**
* Author:
* Date: 2010-11-18
* Source: tinyKACTL
* Description: Minimum Spanning Tree
* Time: $O(|E|\log |E|)$
*/
#pragma once

#include <vector>
#include "../data-structures/UnionFind.h"
using namespace std;

template <class G>
void kruskal(const G *graph, G *tree, int n) {
	typedef typename G::value_type::second_type D;
	UF sets(n);
	vector<pair< D,pair<int,int> > > E;
	// Convert all edges into a single edge-list
	rep(i,0,n)
		trav(e, graph[i])
			if (i < e.first) //Undirected: only use half of the edges
				E.emplace_back(e.second, make_pair(i, e.first));
	sort(E.begin(), E.end());
	rep(i,0,n) tree[i].clear();
	int numEdges = E.size();
	rep(i,0,numEdges) {
		pair<int,int> &e = E[i].second;
		if(!sets.same_set(e.first, e.second)) {
			sets.join(e.first, e.second);
			tree[e.first].emplace_back(e.second, E[i].first);
			tree[e.second].emplace_back(e.first, E[i].first);
		}
	}
}
