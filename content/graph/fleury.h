/**
 * Author: Chen Xing
 * Date: 2009-04-14
 * Source: http://en.wikipedia.org/wiki/Fleury's_algorithm
 * Description: Fleury's Eulerian undirected/directed path/cycle algorithm executor that returns a list of nodes in the Eulerian path/cycle starting from src (or empty if no such cycle/path is available). Code is modifiable to return edges instead of nodes.
 * Time: O(E) where E is the number of edges.
 * Status: Unknown
 */
#pragma once

struct N { vector<pii> outs; }; // (dest, edge index)

vector<int> fleury(vector<N>& nodes, int nedges, int src=0) {
	vector<int> ret, s;
	vector<vector<pii>::iterator> its;
	trav(n, nodes)
		its.push_back(n.outs.begin());
	vector<bool> eu(nedges);
	s.push_back(src);
	while(!s.empty()) {
		int x = s.back();
		auto& it = its[x], end = nodes[x].outs.end();
		while(it != end && eu[it->second]) it++;
		if(it == end) { ret.push_back(x); s.pop_back(); }
		else { s.push_back(it->first); eu[it->second] = true; }
	}
	if(sz(ret) != nedges + 1)
		ret.clear(); // No Eulerian cycles/paths.
	reverse(ret.begin(), ret.end()); // Necessary for directed graphs.
	return ret;
}
