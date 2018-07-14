/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-09
 * License: CC0
 * Source: Basic geometry
 * Description: Returns true iff p lies on the line segment from s to e. Intended for use with e.g. Point<long long> where overflow is an issue. Use (segDist(s,e,p)<=epsilon) instead when using Point<double>.
 * Status:
 */
#pragma once

#include "Point.h"

template<class P>
bool onSegment(const P& s, const P& e, const P& p) {
	P ds = p-s, de = p-e;
	return ds.cross(de) == 0 && ds.dot(de) <= 0;
}
