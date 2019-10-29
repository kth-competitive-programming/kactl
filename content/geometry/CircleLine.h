/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-10-29
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Finds the intersection between a circle and a line. Returns a
 * vector of either 0, 1, or 2 intersection points.
 * Status:
 */

#pragma once

#include "Point.h"
#include "lineDistance.h"
#include "lineProj.h"

template<class P>
vector<P> circleLine(P c, double r, P a, P b) {
	double h2 = r * r - lineDist(a, b, c) * lineDist(a, b, c);
	if (h2 < 0) return {};
	P p = proj(a, b, c);
	if (h == 0) return {p};
	P h = (b-a) * sqrt(h2) / (b-a).dist();
	return {p - h, p + h};
}
