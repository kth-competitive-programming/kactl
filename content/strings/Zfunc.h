/**
 * Author: hhhhaura
 * License: CC0
 * Description: z[x] computes the length of the longest common prefix of s[i:] and s, except z[0] = 0. (abacaba -> 0010301)
 * Time: O(N)
 * Status: stress-tested
 */
#pragma once
<<<<<<< HEAD

vi Z(const string& S) {
	vi z(sz(S));
	int l = -1, r = -1;
	rep(i,1,sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
=======
vi zvalue(string &s) {
	int n = sz(s);
	vi z(n, 0);
	int l = 1, r = 0;
	rep(i, 1, n - 1) {
		z[i] = max(0, min(z[i - l], r - i + 1));
		while(i + z[i] < n && s[i + z[i]] == s[z[i]]) {
			l = i, r = i + z[i], z[i] ++;
		}
>>>>>>> 0efb2e9 (fix Zfunc.h)
	}
	return z;
}


