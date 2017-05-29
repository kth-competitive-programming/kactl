/**
 * Author: tinyKACTL, modified by Ulf Lundstrom
 * Date: 2009-04-04
 * Source:
 * Description: 
 */
#pragma once
#include "Point.h"

template <class P>
struct comparator {
	P o; comparator(P _o) : o(_o) {}
	bool operator ()(const P &p, const P &q) const {
		typename P::coord_type c = (p-o).cross(q-o);
		return c != 0 ? c > 0 : (p-o).dist2() > (q-o).dist2();
	}
};

template <class It>
It convexHull(It begin, It end) {
	typedef typename iterator_traits<It>::value_type P;
	//zero, one or two points always form a hull
	if (end-begin < 2) return end;
	//find a guaranteed hull point and sort in scan order around it
	swap(*begin, *min_element(begin,end));
	comparator<P> comp(*begin);
	sort(begin+1, end, comp);
	//colinear points on first line of the hull must be reversed
	It i = begin+1;
	for (It j = i++; i != end; j = i++) {
		if ((*i-*begin).cross(*j-*begin) != 0)
			break;
	}
	reverse(begin+1, i);
	//place hull points first by doing a Graham scan
	It r = begin + 1;
	for (It i = begin+2; i != end; ++i) {
		while (r > begin && (*r - *(r-1)).cross(*i-*(r-1)) < 0)
			--r;
		swap(*++r, *i);
	}
	if (r == begin+1 && *r == *begin) --r;
	return ++r; //return the iterator past the last hull point
}
