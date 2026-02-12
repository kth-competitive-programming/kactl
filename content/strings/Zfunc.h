/**
 * Author: chilli
 * License: CC0
 * Description: z[i] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vi Z(const string& S) {
	vi z(sz(S));
	int l = 0, r = 0;
	rep(i,1,sz(S)) {
		z[i] = min(max(r - i, 0), z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++, l = i, r = i + z[i];
	}
	return z;
}
