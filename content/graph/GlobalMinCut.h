/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook, http://www.cs.tau.ac.il/~zwick/grad-algo-08/gmc.pdf
 * Description: Find a global minimum cut in an undirected graph, as represented by an adjacency matrix.
 * Time: O(V^3)
 * Status: Lightly tested
 */
#pragma once

pair<int, vi> GetMinCut(vector<vi>& weights) {
	int N = sz(weights);
	vi used(N), cut, best_cut;
	int best_weight = -1;

	for (int phase = N-1; phase >= 0; phase--) {
		vi w = weights[0], added = used;
		int prev, k = 0;
		rep(i,0,phase){
			prev = k;
			k = -1;
			rep(j,1,N)
				if (!added[j] && (k == -1 || w[j] > w[k])) k = j;
			if (i == phase-1) {
				rep(j,0,N) weights[prev][j] += weights[k][j];
				rep(j,0,N) weights[j][prev] = weights[prev][j];
				used[k] = true;
				cut.push_back(k);
				if (best_weight == -1 || w[k] < best_weight) {
					best_cut = cut;
					best_weight = w[k];
				}
			} else {
				rep(j,0,N)
					w[j] += weights[k][j];
				added[k] = true;
			}
		}
	}
	return {best_weight, best_cut};
}
