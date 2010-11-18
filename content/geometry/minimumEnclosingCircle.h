/**
 * Author:
 * Date: 2010-11-18
 * Source: tinyKACTL
 * Description: Fills in $c$ with the centre point of the minimum circle, enclosing the $n$ point vector $p$. The first version fills in indices to the points determining the circle, and returns whether the third index is used. The second version returns the enclosing circle radius as a double. Colinearity of a third point is determined by the eps limit.
 * Time: O(n)
 */
#pragma once

#include "Point.h"

template <class It, class P>
bool mec(It begin, It end, P &c, It &i1, It &i2, It &i3, double eps = 1e-13) {
	typedef typename P::coord type T;
	hull_diameter2(begin, end, i1, i2);
	c = (*i1 + *i2) / 2;
	T r2 = (c-*i1).dist2();
	bool f = false;
	for (int i = 0; i < n; ++i)
		if((c-*i).dist2() > r2) {
			i3 = i, f = true;
			enclosing_centre(*i1, *i2, *i3, c, eps);
			r2 = (c-*i).dist2();
	}
	return f;
}
template <class It, class P>
double mec(It begin, It end, P &c, double eps = 1e-13) {
	It i1, i2, i3;
	mec(begin, end, c, i1, i2, i3, eps);
	return dist(c, *i1);
}
