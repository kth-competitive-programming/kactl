/**
 * Author: Andy Phan
 * Date: 2025-01-25
 * License: CC0
 * Source: me
 * Description: Minimum l such that g(prod(l, r)). Goes in LazySegmentTree.
 * Time: O(\log N).
 */
#pragma once

int min_left(int r, auto g) {
	r += size;
	dip push((r - 1) >> i);
	S sm = ego();
	do {
		r--;
		while (r > 1 && (r % 2)) r /= 2;
		if (!g(op(d[r], sm))) {
		while (r < size) {
			push(r);
			if (g(op(d[r = 2*r+1], sm))) sm = op(d[r--], sm);
		}
		return r + 1 - size;
		}
		sm = op(d[r], sm);
	} while ((r & -r) != r);
	return 0;
}