/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Flow algorithm with guaranteed complexity $O(VE^2)$. To get edge flow values, compare
 * capacities before and after, and take the positive values only.
 * Status: Working
 */
#pragma once

template<class T> T edmondsKarp(vector<map<int, T> >& graph, int source, int sink) {
	if(source == sink) return numeric_limits<T>::max();
	T flow = 0;
	vi prev(sz(graph)), bfs = prev;

	for (;;) {
		fill(all(prev), -1);
		int bfsEnd = 0;
		prev[source] = -2;
		bfs[bfsEnd++] = source;

		for(int i = 0; i < bfsEnd && prev[sink] == -1; ++i) {
			int x = bfs[i];
			trav(e, graph[x]) {
				if(prev[e.first] == -1 && e.second > 0) {
					prev[e.first] = x;
					bfs[bfsEnd++] = e.first;
				}
			}
		}

		if(prev[sink] == -1) break;
		T incrFlow = numeric_limits<T>::max();
		for(int y = sink; prev[y] != -2; y = prev[y])
			incrFlow = min(incrFlow, graph[prev[y]][y]);

		flow += incrFlow;
		for(int y = sink; prev[y] != -2; y = prev[y]) {
			int x = prev[y];
			if((graph[x][y] -= incrFlow) <= 0) graph[x].erase(y);
			graph[y][x] += incrFlow;
		}
	}
	return flow;
}
