/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x, other than s[0..x] itself
 * This is used by find to find all occurances of a string.
 * Time: O(pattern) for pi, O(word + pattern) for find
 * Status: Tested on Kattis, stringmatching
 * Usage:
 *  vi p = pi(pattern); vi occ = find(word, p);
 */
#pragma once
#include <vector>
using namespace std;

vi pi(const string& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vi match(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}
