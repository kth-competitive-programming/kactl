/**
 * Author: Lukas
 * Date: 2009-10-26
 * Source: folklore
 * Description: Segment tree can be used to retrieve maximum
 * of an interval a[x..y]. The array is zero-indexed. You can also update a value a[x].
 * Complexity: Both operations are $O(\log N)$.
 */
#pragma once
#include <vector>
using namespace std;

const int LOW = -1234567890;
struct Tree {
	int n;
	vector<int> s;
	Tree(int _n) {
		n = 1; while (n < _n) n *= 2;
		s.assign(2 * n, 0);
	}
	void udpate(int pos, int val) {
		pos += n;
		while (pos >= 1) {
			s[pos] = max(s[pos], val);
			pos /= 2;
		}
	}
	int query(int a, int b) { return que(1, a, b, 0, n); }
	private:
	int que(int pos, int a, int b, int x, int y) {
		if (a >= b) return LOW;
		if (a == x && b == y) return s[pos];
		int m = (x + y) / 2;
		return max(que(2 * pos, a, min(b, m), x, m),
				que(2 * pos + 1, max(a, m), b, m, y));
	}
};
