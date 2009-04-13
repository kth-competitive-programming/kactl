/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-08
 * Source:
 * Description: Returns the center of mass for the polygon specified by the points between iterators begin and end. It should be an iterator or const\_iterator with value type Point<double>.
 * Status: Tested
 * Usage:
 * 	typedef Point<double> P;
 * 	vector<P> p = ...;
 * 	P com = polygonCenter(p.begin(),p.end());
 */
#pragma once
#include "Point.h"

template <class It>
Point<double> polygonCenter(It begin, It end) {
	Point<double> res;
	double A = 0;
	for (It i = begin, j = end-1; i != end; j=i++) {
		res = res + (*i+*j)*j->cross(*i);
		A += j->cross(*i);
	}
	return res/A/3;
}
