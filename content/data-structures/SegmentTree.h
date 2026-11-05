/**
 * Author: Lucian Bicsi, miie
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed segment tree. Bounds are inclusive to the left and exclusive to the right.
 * $op$ must be associative and $e()$ must return its identity element.
 * Time: O(\log N)
 * Usage: SegTree<int, op, e> tree(n);
 * Status: stress-tested
 */
#pragma once

template <typename T, auto op, auto e>
struct SegTree {
	int n;
	vector<T> data;
	SegTree(int _n): n(_n), data(2*n, e()) {}
	void set(int i, T x) {
		data[i+=n] = x;
		while(i>>=1) { data[i] = op(data[i*2], data[i*2+1]); }
	}
	T prod(int l, int r) {
		T lv = e(), rv = e();
		for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if(l&1) lv = op(lv, data[l++]);
			if(r&1) rv = op(data[--r], rv);
		}
		return op(lv, rv);
	}
};
