/**
 * Author: Simon Lindholm, Victor Lecomte, chilli
 * Date: 2015-09-01
 * License: CC0
 * Description: Computes a pair of points at which two circles intersect. Returns number of intersections. If intersection is only at one point then that point is returned twice.
 * Status: somewhat tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
int circleInter(P a,P b,double r1,double r2,pair<P, P>& out){
	P delta = b - a; double d2 = delta.dist2();
	if (d2 == 0) { assert(r1 != r2); return 0; }
	double p = (d2 + r1*r1 - r2*r2) / (2.0 * d2);
	double h2 = r1*r1 - p*p*d2;
	if (h2 < 0) return 0;
	P mid = a + delta*p, per = delta.perp() * sqrt(h2 / d2);
	out = {mid + per, mid - per};
	return 1 + sgn(h2);
}
