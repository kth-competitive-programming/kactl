
/**
 * Author: chilli
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> 0010123).
 * Description: z[x] computes the length of the longest common prefix of s[i:] and s. (abacaba -> 0010301)
 * Time: O(n)
 * Status: fuzz-tested (thanks to Ludo Pulles)
 */
#pragma once

vi Z(string S) {
	vi z(sz(S));
	int l = -1, r = -1;
	rep(i,1,sz(S)){
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}