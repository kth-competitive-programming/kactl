/**
 * Author: Simon Lindholm
 * Date: 2015-09-01
 * License: CC0
 * Description: Computes the pair of points at which two circles intersect. Returns false in case of no intersection.
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
vector<P> circleInter(P a,P b,double r1,double r2) {
	if (a == b) { assert(r1 != r2); return {}; }
	P vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return {};
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	return {mid + per, mid - per};
}
