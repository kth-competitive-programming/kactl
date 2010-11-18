/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * Source: N/A
 * Description: N/A
 * Status: Working
 */

#include <vector>
#include <map>
using namespace std;

template<class T> T edmondsKarp(vector<map<int, T> >& graph, int source, int sink) {
	if(source == sink) return numeric_limits<T>::max();
	T flow = 0;
	vector<int> prevNode(graph.size()), bfs(graph.size());

	while(true)	{
		fill(prevNode.begin(), prevNode.end(), -1);
		int bfsEnd = 0;
		prevNode[source] = -2;
		bfs[bfsEnd++] = source;

		for(int bfsPos = 0; bfsPos < bfsEnd && prevNode[sink] == -1; ++bfsPos) {
			int x = bfs[bfsPos];
			trav(it, graph[x]) {
				if(prevNode[it->first] == -1 && it->second > 0)	{
					prevNode[it->first] = x;
					bfs[bfsEnd++] = it->first;
				}
			}
		}

		if(prevNode[sink] == -1) break;
		T incrFlow = numeric_limits<T>::max();
		for(int y = sink; prevNode[y] != -2; y = prevNode[y]) {
			int x = prevNode[y];
			incrFlow = min(incrFlow, graph[x][y]);
		}
		flow += incrFlow;
		for(int y = sink; prevNode[y] != -2; y = prevNode[y]) {
			int x = prevNode[y];
			if((graph[x][y] -= incrFlow) <= 0) graph[x].erase(y);
			graph[y][x] += incrFlow;
		}
	}
	return flow;
}
