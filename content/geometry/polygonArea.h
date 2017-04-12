/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * Source: tinyKACTL
 * Description: Returns twice the signed area of a polygon.
 *  Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
 * Status: Tested with unitTest, Kattis problems polygonarea and wrapping and UVa Online Judge Problem: 109 - SCUD Busters
 */
#pragma once
#include "Point.h"

template <class T>
T polygonArea2(vector<Point<T>>& v) {
	auto i = v.begin(), end = v.end(), j = end-1; T a{};
	for (;i != end; j=i++) a += j->cross(*i);
	return a;
}
