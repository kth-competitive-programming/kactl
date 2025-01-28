/**
 * Author: Andy Phan
 * Date: 2025-01-25
 * License: CC0
 * Source: me
 * Description: S: base datatype.
 * S op(S, S): merge S.
 * S ego(): default S, identity for op. F: lazy prop type.
 * S mapping(F, s): apply F to S.
 * F composition(F, F): merge F.
 * F id(): default F, identity for mapping and composition.
 * Time: O(\log N).
 */
#pragma once

// WATCH FOR OUT OF BOUNDS
// template<class S, auto op, auto ego,
//   class F, auto mapping, auto composition, auto id>
struct Tree {
	int n, size, log;
	vector<S> d;
	vector<F> lz;
	Tree(size_t m) {
		n = m; size = bit_ceil(m); log = __lg(size);
		d = vector(2*size, ego());
		lz = vector(size, id());
	}
	void update(int k) { d[k] = op(d[2*k], d[2*k + 1]); }
	void fid(int k, F f) {
		d[k] = mapping(f, d[k]);
		if (k < size) lz[k] = composition(f, lz[k]);
	}
	void push(int k) {
		fid(2 * k, lz[k]);
		fid(2 * k + 1, lz[k]);
		lz[k] = id();
	}
	#define tip for (int i = 1; i <= log; i++)
	#define dip for (int i = log; i >= 1; i--)
	#define check(p) { if (((1<<i)-1) & l) p(l >> i);\
	                   if (((1<<i)-1) & r) p((r-1) >> i); }
	void set(int p, S x) {
		p += size;
		dip push(p >> i);
		d[p] = x;
		tip update(p >> i);
	}
	S prod(int l, int r) {
		l += size; r += size;
		dip check(push);
		S sml = ego(); S smr = ego();
		while (l < r) {
			if (l & 1) sml = op(sml, d[l++]);
			if (r & 1) smr = op(d[--r], smr);
			l /= 2, r /= 2;
		}
		return op(sml, smr);
	}
	void apply(int l, int r, F f) {
		l += size; r += size;
		int l2 = l, r2 = r;
		dip check(push);
		while (l < r) {
			if (l & 1) fid(l++, f);
			if (r & 1) fid(--r, f);
			l /= 2, r /= 2;
		}
		l = l2; r = r2;
		tip check(update);
	}
};
