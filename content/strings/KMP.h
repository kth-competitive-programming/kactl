/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x, other than s[0..x] itself
 * This is used by find to find all occurances of a string.
 * z[x] computes the longest prefix of s that starts at x. Note that z[0] = 0 though, which you often want.
 * It takes pi as input
 * Time: O(pattern) for pi, O(word + pattern) for find
 * Status: Tested on Kattis, stringmatching
 * Usage:
 *  vi p = pi(pattern); vi occ = find(word, p);
 *  vi zf = z(p);
 */
#pragma once

vi pi(const string& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vi z(const vector<int>& p) {
	vi Z(sz(p));
    	rep(i,0,sz(p))
        	Z[i-p[i]+1] = max(Z[i-p[i]+1], p[i]);
    	rep(i,0,sz(p)) if (p[i] && Z[p[i] - 1])
        	Z[i] = max(Z[i], P[Z[P[i] - 1] - 1]);
	return Z;
}

vi match(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}
