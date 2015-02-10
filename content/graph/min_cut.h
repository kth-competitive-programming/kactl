/**
 * Author: Stanford notebook
 * Date: Unknown
 * Source: Stanford notebook
 * Description: Find minimum cut in graph
 * Time: O(V^3)
 * Status: Unknown
 */

#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> vi;

struct Edge {
	int from, to, cap, flow, index;
	Edge(int from, int to, int cap, int flow, int index) :
		from(from), to(to), cap(cap), flow(flow), index(index) {}
};

template<typename Graph>
void AddEdge(Graph& G, int from, int to, int cap) {
	G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
	if (from == to) G[from].back().index++;
	G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
}

const int INF = 1000000000;

pair<int, vi> GetMinCut(vector<vi> &weights) {
	int N = sz(weights);
	vi used(N), cut, best_cut;
	int best_weight = -1;

	for (int phase = N-1; phase >= 0; phase--) {
		vi w = weights[0];
		vi added = used;
		int prev, last = 0;
		rep(i,0,phase){
			prev = last;
			last = -1;
			rep(j,1,N)
				if (!added[j] && (last == -1 || w[j] > w[last])) last = j;
			if (i == phase-1) {
				rep(j,0,N) weights[prev][j] += weights[last][j];
				rep(j,0,N) weights[j][prev] = weights[prev][j];
				used[last] = true;
				cut.push_back(last);
				if (best_weight == -1 || w[last] < best_weight) {
					best_cut = cut;
					best_weight = w[last];
				}
			} else {
				rep(j,0,N)
					w[j] += weights[last][j];
				added[last] = true;
			}
		}
	}
	return make_pair(best_weight, best_cut);
}
