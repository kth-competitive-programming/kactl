/**
 * Author: Chen Xing
 * Date: 2009-04-08
 * Source: http://en.wikipedia.org/wiki/Knuth-Morris-Pratt_algorithm
 * Description: Finds search word in input string.
 * Time: O(W + S) where W = length(word) and S = length(string)
 * Memory: O(W) where W = length(word)
 * Status: Unknown
 * Usage:
 *  string word, input;
 *  KMP<char> kmp(word.begin(), word.end());
 *  vector<int> occ = kmp.findAll(input.begin(), input.end());
 */
#pragma once
#include <vector>
using namespace std;

template<class T>
struct KMP {
	template<class I>
	KMP(I begin, I end) : word(begin, end) {
		table.resize(word.size() + 1, 0);
		table[0] = -1;
		for(unsigned i = 2; i <= word.size(); i++)
			for(int j = table[i - 1]; j >= 0; j = table[j])
				if(word[i - 1] == word[j]) {
					table[i] = j + 1;
					break;
				}
	}

	template<class I>
	vector<int> findAll(I begin, I end) {
		vector<int> res;
		unsigned tp = 0, tl = (end - begin), wp = 0;
		while(tp + wp < tl) {
			if(wp < word.size() && word[wp] == *(begin + tp + wp)) {
				if(++wp == word.size())
					res.push_back(tp); // Break here for "findFirst".
			} else {
				tp += wp - table[wp];
				wp = max(table[wp], 0);
			}
		}
		return res;
	}

	vector<T> word; // Search word.
	vector<int> table; // Partial match table.
};
