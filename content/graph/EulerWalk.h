/**
 * Author: Chen Xing
 * Date: 2009-04-14
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm. Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 *  empty list if no cycle/path exists. To get edge indices back, also put it->second in s (and then ret).
 * Time: O(E) where E is the number of edges.
 * Status: tested
 */
#pragma once

struct V {
	vector<pii> outs; // (dest, edge index)
	int nins = 0;
};

vi euler_walk(vector<V>& nodes, int nedges, int src=0) {
	int c = 0;
	trav(n, nodes) c += abs(n.nins - sz(n.outs));
	if (c > 2) return {};
	vector<vector<pii>::iterator> its;
	trav(n, nodes)
		its.push_back(n.outs.begin());
	vector<bool> eu(nedges);
	vi ret, s = {src};
	while(!s.empty()) {
		int x = s.back();
		auto& it = its[x], end = nodes[x].outs.end();
		while(it != end && eu[it->second]) ++it;
		if(it == end) { ret.push_back(x); s.pop_back(); }
		else { s.push_back(it->first); eu[it->second] = true; }
	}
	if(sz(ret) != nedges+1)
		ret.clear(); // No Eulerian cycles/paths.
	// else, non-cycle if ret.front() != ret.back()
	reverse(all(ret));
	return ret;
}
