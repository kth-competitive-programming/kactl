/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: fuzz-tested a bit
 */
#pragma once

#include "../various/BumpAllocator.h"

const int inf = 1e9;
struct Node {
	Node *L = 0, *R = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			L = new Node(v, lo, mid); R = new Node(v, mid, hi);
			val = max(L->val, R->val);
		}
		else val = v[lo];
	}
	int query(int from, int to) {
		if (to <= lo || hi <= from) return -inf;
		if (from <= lo && hi <= to) return val;
		push();
		return max(L->query(from, to), R->query(from, to));
	}
	void set(int from, int to, int x) {
		if (to <= lo || hi <= from) return;
		if (from <= lo && hi <= to) mset = val = x, madd = 0;
		else {
			push(), L->set(from, to, x), R->set(from, to, x);
			val = max(L->val, R->val);
		}
	}
	void add(int from, int to, int x) {
		if (to <= lo || hi <= from) return;
		if (from <= lo && hi <= to) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), L->add(from, to, x), R->add(from, to, x);
			val = max(L->val, R->val);
		}
	}
	void push() {
		if (!L) {
			int mid = lo + (hi - lo)/2;
			L = new Node(lo, mid); R = new Node(mid, hi);
		}
		if (mset != inf)
			L->set(lo,hi,mset), R->set(lo,hi,mset), mset = inf;
		else if (madd)
			L->add(lo,hi,madd), R->add(lo,hi,madd), madd = 0;
	}
};
