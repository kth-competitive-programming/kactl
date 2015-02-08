/**
 * Description: Weighted matching
 * Author: github
 * Source: github
 * Date: today
 * Time: $O(N^4)$ probably.
 */

#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

double MinCostMatching(const vector<vector<double>> &cost, vi &Lmate, vi &Rmate) {
	int n = int(cost.size());

	// construct dual feasible solution
	vector<double> u(n);
	vector<double> v(n);
	rep(i,0,n){
		u[i] = cost[i][0];
		rep(j,1,n) u[i] = min(u[i], cost[i][j]);
	}
	rep(j,0,n){
		v[j] = cost[0][j] - u[0];
		rep(i,1,n) v[j] = min(v[j], cost[i][j] - u[i]);
	}

	// construct primal solution satisfying complementary slackness
	Lmate = vi(n, -1);
	Rmate = vi(n, -1);
	int mated = 0;
	rep(i,0,n) rep(j,0,n) {
		if (Rmate[j] != -1) continue;
		if (fabs(cost[i][j] - u[i] - v[j]) < 1e-10) {
			Lmate[i] = j;
			Rmate[j] = i;
			mated++;
			break;
		}
	}

	vector<double> dist(n);
	vi dad(n);
	vi seen(n);

	// repeat until primal solution is feasible
	while (mated < n) {

		// find an unmatched left node
		int s = 0;
		while (Lmate[s] != -1) s++;

		// initialize Dijkstra
		fill(dad.begin(), dad.end(), -1);
		fill(seen.begin(), seen.end(), 0);
		rep(k,0,n)
			dist[k] = cost[s][k] - u[s] - v[k];

		int j = 0;
		while (true) {

			// find closest
			j = -1;
			rep(k,0,n){
				if (seen[k]) continue;
				if (j == -1 || dist[k] < dist[j]) j = k;
			}
			seen[j] = 1;

			// termination condition
			if (Rmate[j] == -1) break;

			// relax neighbors
			const int i = Rmate[j];
			rep(k,0,n){
				if (seen[k]) continue;
				const double new_dist = dist[j] + cost[i][k] - u[i] - v[k];
				if (dist[k] > new_dist) {
					dist[k] = new_dist;
					dad[k] = j;
				}
			}
		}

		// update dual variables
		rep(k,0,n){
			if (k == j || !seen[k]) continue;
			const int i = Rmate[k];
			v[k] += dist[k] - dist[j];
			u[i] -= dist[k] - dist[j];
		}
		u[s] += dist[j];

		// augment along path
		while (dad[j] >= 0) {
			const int d = dad[j];
			Rmate[j] = Rmate[d];
			Lmate[Rmate[j]] = j;
			j = d;
		}
		Rmate[j] = s;
		Lmate[s] = j;

		mated++;
	}

	double value = 0;
	rep(i,0,n)
		value += cost[i][Lmate[i]];

	return value;
}

