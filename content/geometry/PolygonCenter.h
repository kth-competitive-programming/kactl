/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-08
 * License: CC0
 * Source:
 * Description: Returns the center of mass for a polygon.
 * Status: Tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
Point<double> polygonCenter(vector<P>& v) {
	auto i = v.begin(), end = v.end(), j = end-1;
	Point<double> res{0,0}; double A = 0;
	for (; i != end; j=i++) {
		res = res + (*i + *j) * j->cross(*i);
		A += j->cross(*i);
	}
	return res / A / 3;
}
