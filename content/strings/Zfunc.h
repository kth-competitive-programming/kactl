/**
 * Author: hhhhaura
 * License: CC0
 * Description: z[x] computes the length of the longest common prefix of s[i:] and s, except z[0] = 0. (abacaba -> 0010301)
 * Time: O(N)
 * Status: stress-tested
 */
#pragma once
vi Z(const string &s) {
	int n = sz(s);
	vi z(n, 0);
	int l = 1, r = 0;
	rep(i, 1, n - 1) {
		z[i] = max(0, min(z[i - l], r - i + 1));
		while(i + z[i] < n && s[i + z[i]] == s[z[i]]) {
			l = i, r = i + z[i], z[i] ++;
		}
	}
	return z;
}


