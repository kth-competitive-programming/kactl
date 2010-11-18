/**
 * Author: André Susano Pinto
 * Date: 2010-11-10
 * Source:
 * Description: Returns the max submatrix sum (empty submatrix is valid).
 * Status: Not tested
 * Time: O(n^3)
 */
#pragma once

int maxsubmatrixsum(const vector<vi> &mat) {
	int N = mat.size(); int M = mat[0].size();
	int best = 0; // set to inf for not allowing empty submatrix.
	rep(i, 0, N) {
		vector<int> sub(M);
		rep(j, i, N) {
			rep(k, 0, M) sub[k] += mat[j][k];

			// Max subsequence over sub.
			int sum = 0;
			rep(upper, 0, seq.size()) {
				if(sum < 0) sum = 0;
				sum += seq[upper];
				best = max(best, sum);
			}
		}
	}
	return best;
}
