/**
 * Author: Lukas
 * Date: 2009-10-30
 * Source: folklore/TopCoder
 * Description: Fenwick tree can be used to retrieve
 * cumulative sum a[1...x] of and array. You can also update
 * the value a[x] (update function takes the diference between
 * old and new value).
 * Complexity: Both operations are $O(\log N)$.
 */
#pragma once
#include <vector>
using namespace std;

struct FenwickTree
{
	int n;
	vector<int> s;
	FenwickTree(int _n) : n(_n) {
		s.assign(n, 0);
	}
	void update(int pos, int dif) {
		while (pos < n) {
			s[pos] += dif;
			pos |= pos + 1;
		}
	}
	int query(int val) {
		int count = 0;
		while (val >= 0) {
			count += s[val];
			val = (val & (val + 1)) - 1;
		}
		return count;
	}
};
