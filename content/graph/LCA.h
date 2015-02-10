/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * Source: Folklore
 * Status: Tested at Petrozavodsk
 * Description: Lowest common ancestor. Finds the lowest common
 * ancestor in a tree. C should be an adjacency list of the tree
 * and P should be a vector containing the parents of all the
 * nodes. Can also find the distance between two nodes.
 * Usage:
 *  LCA lca(tree, parents); 
 *  lca.query(firstNode, secondNode);
 *  lca.distance(firstNode, secondNode);
 * Time: $O(|V| \log |V| + Q)$
 */

#pragma once

#include "../data structures/RMQ.h"
#include <vector>

using namespace std;

typedef vector<pii> vpi;
const pii inf(1 << 29, -1);

struct LCA {
	int time;
	vi start, end;
	vector<ll> dist;
	RMQ<pii> rmq;

	LCA(vector<vpi>& C){
		int on = 1, depth = 1;
		while(on < (int)C.size()) on*=2, depth++;
		start.resize(C.size());
		end.resize(C.size());
		dist.resize(C.size());
		time = 0;
		vector<pii> D;
		dfs(0, -1, 0, 0, D, C);
		rmq.init(D);
	}

	void dfs(int v, int p, int d, ll dst,
			vpi& D, vector<vpi>& C){
		dist[v] = dst;
		D.push_back(pii(d, v));
		start[v] = time++;
		trav(it, C[v]) if(it->first != p){
			dfs(it->first, v, d+1, dst + it->second, D, C);
			D.push_back(pii(d, v));
			time++;
		}
		end[v] = time++;
		D.push_back(pii(d, v));
	}

	pii query(int a, int b){
		return rmq.query(
				min(start[a], start[b]),
				max(end[a], end[b]) + 1);
	}

	ll distance(int a, int b){
		pii lca = query(a, b);
		return dist[a] + dist[b] - 2 * dist[lca.second];
	}
};
