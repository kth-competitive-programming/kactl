/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * Source: Folklore
 * Description: Depth-first search. Calculates start
 * and end time as well as depths.
 * Status: Tested (at Petrozavodsk)
 * Time: $O(|E| + |V|)$
 */
#pragma once

#include <vector>
using namespace std;

typedef vector<pii> vpi;
struct DFS {
	int t, d;
	vi start, end, depth;

	DFS(vector<vpi>& C) : t(0), d(0),
	start(C.size()), end(C.size()),
	depth(C.size()) { dfs(0, -1, C); }

	void dfs(int v, int p, vector<vpi>& C){
		start[v] = t++, depth[v] = d++;
		trav(it, C[v]) if(it->first != p) dfs(it->first, v, C);
		d--;
		end[v] = t++;
	}
};
