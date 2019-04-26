/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-22
 * License: CC0
 * Source: Basic geometry
 * Description: Returns true if p lies within the polygon described by the points between iterators begin and end. If strict false is returned when p is on the edge of the polygon. Answer is calculated by counting the number of intersections between the polygon and a line going from p to infinity in the positive x-direction. The algorithm uses products in intermediate steps so watch out for overflow. If points within epsilon from an edge should be considered as on the edge replace the line "if (onSegment..." with the comment bellow it (this will cause overflow for int and long long).
 * Time: O(n)
 * Status: tested with unitTest and Kattis problems copsrobbers, pointinpolygon and intersection
 * Usage:
 * 	typedef Point<int> pi;
 * 	vector<pi> v; v.push_back(pi(4,4));
 * 	v.push_back(pi(1,2)); v.push_back(pi(2,1));
 * 	bool in = insidePolygon(v.begin(),v.end(), pi(3,4), false);
 */
#pragma once

#include "Point.h"
#include "onSegment.h"

template<class P> bool crossesRay(P a, P p, P q) {
	return sgn(((a.y>=q.y) - (a.y>=p.y)) * a.cross(p, q)) > 0;
}
template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
		int nCross = 0, n = sz(p);
		rep(i, 0, n) {
				if (onSegment(p[i], p[(i + 1) % n], a)) return !strict;
				nCross += crossesRay(a, p[i], p[(i + 1) % n]);
		}
		return nCross & 1;
}
