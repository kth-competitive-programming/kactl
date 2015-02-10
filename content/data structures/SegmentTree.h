/**
 * Author: Lukas Polacek, Johan Sannemo
 * Date: 2009-10-26, 2015-02-10
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right. The tree can be changed by modifying T, LOW and f.
 * Time: O(\log N).
 */
#pragma once
#include <vector>
using namespace std;

struct Tree {
	typedef int T;
	const T LOW = -1234567890;
	T f(T a, T b) { return max(a, b); }

	int n;
	vi s;
	Tree() {} 
	Tree(int _n, T def=0) { init(_n, def); }
	void init(int _n, T def){
		n = 1; while (n < _n) n *= 2;
		s.assign(n + _n, def);
		s.resize(2 * n, LOW);
		for(int i = n - 1; i >= 1; --i)
			s[i] = f(s[i * 2], s[i*2 + 1]);
	}
	void update(int pos, T val) {
		pos += n;
		s[pos] = val;
		for (pos /= 2; pos >= 1; pos /= 2)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int a, int b) { return que(1, a, b, 0, n); }
	T que(int pos, int a, int b, int x, int y) {
		if (a >= b) return LOW;
		if (a == x && b == y) return s[pos];
		int m = (x + y) / 2;
		return f(que(2 * pos, a, min(b, m), x, m),
				que(2 * pos + 1, max(a, m), b, m, y));
	}
};
