/**
 * Author: Sachin Sivakumar
 * Date: 2025-01-23
 * Description: Computes the Lyndon Factorization of a string. A Lyndon word is a 
 * nonempty string that is strictly smaller in lexicographic order than any of its 
 * proper suffixes. Returns the starting indices of the Lyndon words in the string.
 * Time: O(n)
 * Status: Tested on CSES Minimal Rotation
 */
#pragma once

vi duval(string &s) {
	vi ans;
	for(int start = 0; start < sz(s);) {
		int i = start+1, j = start;
		for(; i < sz(s) && s[i] >= s[j]; i++)
			if(s[i] > s[j]) j = start;
			else j++;
		for(int sz = i-j; start + sz <= i; start += sz)
			ans.push_back(start);
	}
	return ans;
}
