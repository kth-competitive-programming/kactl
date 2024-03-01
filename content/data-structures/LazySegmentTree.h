/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once

#include "../various/BumpAllocator.h"

const ll inf = 1e9;
struct Node {
	typedef ll T; // data type
	struct L { ll mset, madd; }; // lazy type
	const T tneut = -inf;     // neutral elements
	const L lneut = {inf, 0};
	T f (T a, T b) { return max(a, b); } // (any associative fn)
	T apply (T a, L b) {
		return b.mset != inf ? b.mset + b.madd : a + b.madd;
	} // Apply lazy
	L comb(L a, L b) {
		if (b.mset != inf) return b;
		return {a.mset, a.madd + b.madd};
	} // Combine lazy

	Node *l = 0, *r = 0;
	ll lo, hi; T val = tneut; L lazy = lneut;
	Node(ll lo,ll hi):lo(lo),hi(hi){}//Large interval of tneut
	Node(vector<T>& v, ll lo, ll hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			ll mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = f(l->val, r->val);
		}
		else val = v[lo];
	}
	T query(ll L, ll R) {
		if (R <= lo || hi <= L) return tneut;
		if (L <= lo && hi <= R) return apply(val, lazy);
		push();
		return f(l->query(L, R), r->query(L, R));
	}
	void upd(ll Le, ll Ri, L x) {
		if (Ri <= lo || hi <= Le) return;
		if (Le <= lo && hi <= Ri) lazy = comb(lazy, x);
		else {
			push(), l->upd(Le, Ri, x), r->upd(Le, Ri, x);
			val = f(l->query(lo, hi), r->query(lo, hi));
		}
	}
	void set(ll L, ll R, ll x) { upd(L, R, {x, 0}); }
	void add(ll L, ll R, ll x) { upd(L, R, {inf, x}); }
	void push() {
		if (!l) {
			ll mid = lo + (hi - lo)/2;
			l = new Node(lo, mid), r = new Node(mid, hi);
		}
		l->lazy = comb(l->lazy, lazy);
		r->lazy = comb(r->lazy, lazy);
		lazy = lneut;
		val = f(l->query(lo, hi), r->query(lo, hi));
	}
};
