/**
 * Author: André Susano Pinto
 * Date: 2010-11-10
 * Description: Returns the max subquence sum (empty subsequence is valid).
 * Status: Not tested
 * Time: O(n)
 */
#pragma once

int maxsubsequence(const vi& seq) {
	int low = 0, sum = 0, best = 0;
	rep(upper, 0, seq.size()) {
		while(sum <= 0 && low < upper) sum -= seq[low++];
		sum += seq[upper];
		best = max(best, sum);
	}
	return best;
}
