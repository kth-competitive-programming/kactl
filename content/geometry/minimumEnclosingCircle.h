/**
 * Author:
 * Date: 2010-11-18
 * Source: tinyKACTL
 * Description: Fills in $c$ with the centre point of the minimum circle, enclosing the $n$ point vector $p$. The first version fills in indices to the points determining the circle, and returns whether the third index is used. The second version returns the enclosing circle radius as a double.
 * Time: O(n)
 */
#pragma once

#include "Point.h"
#include "circumcircle.h"

template <class It, class T, class P = Point<T> >
bool mec(It begin, It end, P &c, It &i1, It &i2, It &i3) {
	hull_diameter2(begin, end, i1, i2); // (good luck)
	c = (*i1 + *i2) / 2;
	T r2 = (c-*i1).dist2();
	bool f = false;
	for (It i = begin; i != end; ++i)
		if((c-*i).dist2() > r2) {
			i3 = i, f = true;
			c = ccCenter(*i1, *i2, *i3);
			r2 = (c-*i).dist2();
	}
	return f;
}
template <class It, class P>
double mec(It begin, It end, P &c) {
	It i1, i2, i3;
	mec(begin, end, c, i1, i2, i3);
	return (c - *i1).dist();
}
