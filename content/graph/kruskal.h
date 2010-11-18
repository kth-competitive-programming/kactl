/**
* Author:
* Date: 2010-11-18
* Source: tinyKACTL
* Description: Minimum Spanning Tree
*/
#pragma once

#include <vector>
#include "../data structures/union_find.h"
using namespace std;

template <class G>
void kruskal(const G *graph, G *tree, int n) {
	typedef typename G::const_iterator G_iter;
	typedef typename G::value_type::second_type D;
	union_find sets(n);
	vector<pair< D,pair<int,int> > > E;
	// Convert all edges into a single edge-list
	for( int i=0; i<n; i++ )
		for(G_iter it = graph[i].begin(); it!=graph[i].end(); ++it)
			if (i < it->first) //Undirected: only use half of the edges
				E.push_back(make_pair(it->second, make_pair(i, it->first)));
	sort(E.begin(), E.end());
	for(int i=0; i<n; i++) tree[i].clear();
	int numEdges = E.size();
	for(int i = 0; i < numEdges; ++i) {
		pair<int,int> &e = E[i].second;
		if(!sets.same_set(e.first, e.second)) {
			sets.join(e.first, e.second);
			tree[e.first].push_back(make_pair(e.second, E[i].first));
			tree[e.second].push_back(make_pair(e.first, E[i].first));
		}
	}
}
