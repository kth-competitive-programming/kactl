/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow. cap[i][j] != cap[j][i] is allowed; negative costs probably are not.
 * To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis mincostmaxflow
 */
#pragma once
#include <vector>
using namespace std;

typedef long long L;
typedef vector<L> vl;

const L INF = numeric_limits<L>::max() / 4;

struct MinCostMaxFlow {
	int N;
	vector<vl> cap, flow, cost;
	vi found;
	vl dist, pi, width;
	vector<pii> dad;

	MinCostMaxFlow(int N) :
		N(N), cap(N, vl(N)), flow(N, vl(N)), cost(N, vl(N)),
		found(N), dist(N), pi(N), width(N), dad(N) {}

	void AddEdge(int from, int to, L cap, L cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
	}

	void Relax(int s, int k, L cap, L cost, int dir) {
		L val = dist[s] + pi[s] - pi[k] + cost;
		if (cap && val < dist[k]) {
			dist[k] = val;
			dad[k] = {s, dir};
			width[k] = min(cap, width[s]);
		}
	}

	L Dijkstra(int s, int t) {
		fill(all(found), 0);
		fill(all(dist), INF);
		fill(all(width), 0);
		dist[s] = 0;
		width[s] = INF;

		while (s != -1) {
			int best = -1;
			found[s] = 1;
			rep(k,0,N) {
				if (found[k]) continue;
				Relax(s, k, cap[s][k] - flow[s][k], cost[s][k], 1);
				Relax(s, k, flow[k][s], -cost[k][s], -1);
				if (best == -1 || dist[k] < dist[best]) best = k;
			}
			s = best;
		}

		rep(k,0,N)
			pi[k] = min(pi[k] + dist[k], INF);
		return width[t];
	}

	pair<L, L> GetMaxFlow(int s, int t) {
		L totflow = 0, totcost = 0;
		while (L amt = Dijkstra(s, t)) {
			totflow += amt;
			for (int x = t; x != s; x = dad[x].first) {
				if (dad[x].second == 1) {
					flow[dad[x].first][x] += amt;
					totcost += amt * cost[dad[x].first][x];
				} else {
					flow[x][dad[x].first] -= amt;
					totcost -= amt * cost[x][dad[x].first];
				}
			}
		}
		return {totflow, totcost};
	}
};
