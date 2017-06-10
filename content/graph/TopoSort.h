/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sorting. Given is an oriented graph.
 * Output is an ordering of vertices (array idx), such that there are edges
 * only from left to right. The function returns false if there is a cycle in
 * the graph.
 * Time: $O(|V|+|E|)$
 */
#pragma once

template <class E, class I>
bool topo_sort(const E &edges, I &idx, int n) {
	vi indeg(n);
	rep(i,0,n)
		trav(e, edges[i])
			indeg[e]++;
	queue<int> q; // use priority queue for lexic. smallest ans.
	rep(i,0,n) if (indeg[i] == 0) q.push(-i);
	int nr = 0;
	while (q.size() > 0) {
		int i = -q.front(); // top() for priority queue
		idx[i] = ++nr;
		q.pop();
		trav(e, edges[i])
			if (--indeg[e] == 0) q.push(-e);
	}
	return nr == n;
}
