/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-10-29
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Finds the intersection between a circle and a line. Returns a
 * vector of either 0, 1, or 2 intersection points. P is intended to be
 * Point<double>
 * Status: unit tested
 */

#pragma once

#include "Point.h"
#include "lineDistance.h"
#include "LineProjectionReflection.h"

template<class P>
vector<P> circleLine(P c, double r, P a, P b) {
	double h2 = r*r - b.cross(a,c)*b.cross(a,c)/(b-a).dist2();
	if (h2 < 0) return {};
	P p = lineProj(a, b, c);
	if (h2 == 0) return {p};
	P h = (b-a) * sqrt(h2) / (b-a).dist();
	return {p - h, p + h};
}
