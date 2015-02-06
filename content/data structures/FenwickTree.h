/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * Source: folklore/TopCoder
 * Description: In the beginning there is an array $a[n]$ full of zeroes.
 * Fenwick tree can be used to retrieve sum $a[0]+\dots+a[x]$. You
 * can also update the value $a[x]$ (update function takes the difference
 * between the old and new value).
 * Time: Both operations are $O(\log N)$.
 */
#pragma once
#include <vector>
using namespace std;

struct FT {
	int n;
	vi s;
	FT(int _n) : n(_n) {
		s.assign(n, 0);
	}
	void update(int pos, int dif) {
		for (; pos < n; pos |= pos + 1)
			s[pos] += dif;
	}
	int query(int pos) {
		int count = 0;
		for (; pos >= 0; pos = (pos & (pos + 1)) - 1)
			count += s[pos];
		return count;
	}
};
