/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-10-31
 * License: CC0
 * Source:
 * Description: Returns the external tangents of two circles, where P1 and P2
 * are the tangency points of circle 1 and 2 respectively. Can return 0, 1, or
 * 2 tangents. If the circles are the same, returns 0 tangents. If there is
 * only 1 tangent, then the circles are tangent to each other at some point P,
 * and the tangent line can be found as the perpendicular line c1 -> P passing
 * through P. Internal tangents can be found by negating r2. To find the
 * tangents of a circle with a point c2 set r2 to 0.
 * Status: tested
 * Usage:
 */
#pragma once

#include "Point.h"

template<class P>
vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
	P d = c2 - c1;
	double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
	if (d2 == 0 || h2 < 0)  return {};
	vector<pair<P, P>> out;
	for (double sign : {-1, 1}) {
		P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
		out.push_back({c1 + v * r1, c2 + v * r2});
	}
	if (h2 == 0) out.pop_back();
	return out;
}
