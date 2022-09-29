/**
 * Author: hhhhaura
 * Description: Computes the longest palindromic subsequence in string. even indices are padded with char '.'.
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

int Manacher(string &s) {
	string t = ".";
	rep(i, 0, sz(s) - 1) t += s[i] + '.';
	int n = sz(t), l = 0, r = 0;
	vi v(n, 1);
	rep(i, 1, n - 1) {
		v[i] = max(1, min(v[l + l - i], r - i + 1));
		while(0 <= i - v[i] && i + v[i] < n && t[i + v[i]] == t[i - v[i]]) {
			l = i, r = i + v[i], v[i] ++;
		}
	}
	return *max_element(all(v)) - 1;
}
