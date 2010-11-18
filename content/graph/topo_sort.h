/**
 * Author:
 * Date: 2010-11-18
 * Source: tinyKACTL
 * Description:
 */
#pragma once

#include <vector>
#include <queue>
using namespace std;

template <class E, class I>
bool topo sort(const E *edges, I &idx, int n) {
	typedef typename E::const iterator E iter;
	vector<int> indeg(n);
	for (int i = 0; i < n; i++)
		for (E iter e = edges[i].begin(); e != edges[i].end(); e++)
		indeg[*e]++;
	queue<int> q; // use priority queue for lexic. smal lest ans.
	for (int i = 0; i < n; i++)
		if (indeg[i] == 0) q.push(-i);
	int nr = 0;
	while (q.size() > 0) {
		int i = -q.front(); // top() for priority queue
		idx[i] = ++nr;
		q.pop();
		for (E iter e = edges[i].begin(); e != edges[i].end(); ++e)
			if (--indeg[*e] == 0) q.push(-*e);
	}
	return nr == n;
}
