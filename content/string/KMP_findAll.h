/**
 * Author: Chen Xing
 * Date: 2009-03-13
 * Source: http://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 * Description: Finds all occurrences of the word "W" in string "S". 
 * Time: O(n) where n = length(S)
 * Memory: O(n) where n = length(S)
 * Status: Unknown
 * Usage:
 * 	string word = "s a";
 * 	string text = "This is a text, is a text!";
 * 	vector<int> positions = KMP_findAll(KMP<char>(word.begin(), word.end()), text.begin(), text.end());
 * Changes:
 */
#pragma once

#include "KMP.h"

template<class Ty, class It>
vector<int> KMP_findAll(const KMP<Ty>& kmp, It begin, It end) {
	vector<int> res;
	int tp = 0, tl = (end - begin), wp = 0;
	while(tp + wp < tl) {
		if(wp < kmp.word.size() && kmp.word[wp] == *(begin + tp + wp)) {
			if(++wp == kmp.word.size())
				res.push_back(tp);
		} else {
			tp += wp - kmp.table[wp];
			wp = max(kmp.table[wp], 0);
		}
	}
	return res;
}
