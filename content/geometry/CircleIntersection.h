/**
 * Author: Simon Lindholm, Victor Lecomte, chilli
 * Date: 2015-09-01
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Computes a pair of points at which two circles intersect. Returns false in case of no intersection.
 * Status: somewhat tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
int circleInter(P a,P b,double r1,double r2,pair<P, P>* out){
	if (a == b) { assert(r1 != r2); return false; }
	P delta = b - a;
	double d2 = delta.dist2(), p = (d2 + r1*r1 - r2*r2)/(d2*2);
	double h2 = r1*r1 - p*p*d2;
	if (h2 < 0) return false;
	P mid = a + delta*p, per = delta.perp() * sqrt(h2 / d2);
	*out = {mid + per, mid - per};
	return true;
}
