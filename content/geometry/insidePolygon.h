/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true if p lies within the polygon. If p is on the edge of the polygon, it returns false when strict is true. Answer is calculated by counting the number of intersections between the polygon and a line going from p to infinity in the positive x-direction. The algorithm uses products in intermediate steps so watch out for overflow.
 * Time: O(n)
 * Status: fuzz-tested
 * Usage:
 * 	typedef Point<int> P;
 * 	vector<P> v; v.push_back(P(4,4));
 * 	v.push_back(P(1,2)); v.push_back(P(2,1));
 * 	bool in = insidePolygon(v, P(3,4), false);
 */
#pragma once

#include "Point.h"
#include "onSegment.h"

template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
		int nCross = 0, n = sz(p);
		rep(i, 0, n) {
			if (onSegment(p[i], p[(i + 1) % n], a)) return !strict;
			nCross += (sgn(a.y >= p[(i + 1) % n].y) -
				sgn(a.y>=p[i].y)) * sgn(a.cross(p[i], p[(i+1)%n])) > 0;
		}
		return nCross & 1;
}
