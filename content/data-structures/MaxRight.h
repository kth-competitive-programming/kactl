/**
 * Author: Andy Phan
 * Date: 2025-01-25
 * License: CC0
 * Source: me
 * Description: Maximum r such that g(prod(l, r)). Goes in LazySegmentTree.
 * Time: O(\log N).
 */
#pragma once

int max_right(int l, auto g) {
	l += size;
	dip push(l >> i);
	S sm = ego();
	do {
	while (l % 2 == 0) l /= 2;
	if (!g(op(sm, d[l]))) {
		while (l < size) {
			push(l);
			if (g(op(sm, d[l *= 2]))) sm = op(sm, d[l++]);
		}
		return l - size;
	}
	sm = op(sm, d[l++]);
	} while ((l & -l) != l);
	return n;
}