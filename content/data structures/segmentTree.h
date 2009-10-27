/**
 * Author: Lukas
 * Date: 2009-10-26
 * Source: folklore
 * Description: MaxTree is for operation maximum and FenwickT.
 * is for operation plus. Query on an interval [a, b] for
 * Fenwick is query(b) - query(a - 1)
 */
#pragma once
#include <vector>
using namespace std;

const int LOW = -1234567890;
struct MaxTree {
	int n;
	vector<int> s;
	MaxTree(int _n) {
		n = 1; while (n < _n) n *= 2;
		s.assign(2 * n, 0);
	}
	void insert(int pos, int val) {
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
struct FenwickTree
{
	int n;
	vector<int> s;
	FenwickTree(int _n) : n(_n) {
		s.assign(n, 0);
	}
	void insert(int pos, int val) {
		while (pos < n) {
			s[pos] += val;
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
