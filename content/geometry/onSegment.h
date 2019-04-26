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

template <class P> bool onSegment(P s, P e, P p) {
	return sgn(s.cross(e, p)) == 0 && sgn((s - p).dot(e - p)) <= 0;
}
