/**
 * Author: Chen Xing
 * Date: 2009-03-13
 * Source: http://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 * Description: KMP data structure holding search "word" W and partial match table T.
 * Time: O(m) where m = length(W)
 * Memory: O(m) where m = length(W)
 * Status: Unknown
 * Usage:
 * 	vector<int> word;
 * 	KMP<int> wordKMP(word.begin(), word.end());
 * Changes:
 */
#pragma once

template<class Ty>
struct KMP {
	template<class It> KMP(It begin, It end):
		word(begin, end)
	{
		table.resize(word.size() + 1, 0);
		table[0] = -1;
		for(int i = 2; i <= word.size(); i++) {
			for(int j = table[i - 1]; j >= 0; j = table[j]) {
				if(word[i - 1] == word[j]) {
					table[i] = j + 1;
					break;
				}
			}
		}
	}

	vector<Ty> word;
	vector<int> table;
};
