/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * Source: tinyKACTL
 * Description: Returns twice the signed area of the polygon made up from the points between iterators begin and end. Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
 * Usage:
 *  vector<Point<double>> v;
 * 	double A = polygonArea2<double>(v.begin(),v.end())/2;
 * Time: O(n)
 * Status: Tested with unitTest, Kattis problems polygonarea and wrapping and UVa Online Judge Problem: 109 - SCUD Busters

 */
#pragma once
#include "Point.h"

template <class T, class It>
T polygonArea2(It begin, It end) {
	T a{};
	for (It i = begin, j = end-1; i != end; j=i++)
		a += j->cross(*i);
	return a;
}
