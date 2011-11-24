/**
* Author:
* Date: 2010-11-18
* Source: tinyKACTL
* Description: Minimum Spanning Tree
* Time: $O(|E|\log |E|)$
*/
#pragma once

#include <vector>
#include "../data structures/union_find.h"
using namespace std;

template <class G>
void kruskal(const G *graph, G *tree, int n) {
	typedef typename G::value_type::second_type D;
	union_find sets(n);
	vector<pair< D,pair<int,int> > > E;
	// Convert all edges into a single edge-list
	rep(i,0,n)
		trav(it, graph[i])
			if (i < it->first) //Undirected: only use half of the edges
				E.push_back(make_pair(it->second, make_pair(i, it->first)));
	sort(E.begin(), E.end());
	rep(i,0,n) tree[i].clear();
	int numEdges = E.size();
	rep(i,0,numEdges) {
		pair<int,int> &e = E[i].second;
		if(!sets.same_set(e.first, e.second)) {
			sets.join(e.first, e.second);
			tree[e.first].push_back(make_pair(e.second, E[i].first));
			tree[e.second].push_back(make_pair(e.first, E[i].first));
		}
	}
}
