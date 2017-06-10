/**
 * Author: Simon Lindholm
 * Date: 2015-09-01
 * License: CC0
 * Description: Computes a pair of points at which two circles intersect. Returns false in case of no intersection.
 * Status: somewhat tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
bool circleIntersection(P a, P b, double r1, double r2,
		pair<P, P>* out) {
	P delta = b - a;
	assert(delta.x || delta.y || r1 != r2);
	if (!delta.x && !delta.y) return false;
	double r = r1 + r2, d2 = delta.dist2();
	double p = (d2 + r1*r1 - r2*r2) / (2.0 * d2);
	double h2 = r1*r1 - p*p*d2;
	if (d2 > r*r || h2 < 0) return false;
	P mid = a + delta*p, per = delta.perp() * sqrt(h2 / d2);
	*out = {mid + per, mid - per};
	return true;
}
