/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * Source:
 * Description: Returns a vector with the vertices of the polygon created from the points between begin and end with everything to the left of the line going from s to e cut away. P can be e.g. Point<double> or Point<int> and It should be an iterator const_iterator with value type P. Products are used in intermediate steps so watch out for overflow.
 * Status: tested but not extensivly
 * Usage:
 * 	typedef Point<double> P;
 * 	vector<P> p = ...;
 * 	p = polygonCut(p.begin(),p.end(),P(0,0),P(1,0));
 */
#pragma once
#include "Point.h"
#include "lineIntersection.h"

template <class P, class It>
vector<P> polygonCut(It begin, It end, P s, P e) {
	vector<P> res;
	if (begin == end) return res;
	for (It i = begin, j = end-1; i != end; j = i++) {
		bool side = (e-s).cross(*i-s) < 0;
		if (side != ((e-s).cross(*j-s)<0)) {
			res.push_back(P());
			lineIntersection(s, e, *i, *j, res.back());
		}
		if (side)
			res.push_back(*i);
	}
	return res;
}
