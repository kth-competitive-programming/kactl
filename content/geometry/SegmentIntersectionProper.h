/**
 * Author: Ulf Lundstrom, Simon Lindholm
 * Date: 2016-09-24
 * License: CC0
 * Source: SegmentIntersection.h
 * Description: Like segmentIntersection, but only returns true/false.
 * Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
 * Status: Relatively well tested.
 */
#pragma once

#include "Point.h"

template <class P>
bool segInterProper(P a, P b, P c, P d, P &out) {
	double oa = c.cross(d, a), ob = c.cross(d, b),
		   oc = a.cross(b, c), od = a.cross(b, d);
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
		out = (a * ob - b * oa) / (ob - oa);
		return true;
	}
	return false;
}