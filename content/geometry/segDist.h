/**
Author: Ulf Lundstrom
Date: 2009-03-21
Description: Returns the shortest distance between point p and the line segment from point s to e. P is supposed to be Point<T> where T is e.g. double or long long. It uses products of six coordinates in intermediate steps so never use T=int and only T=long long if all coordinates are smaller than 512.
Status: tested
Usage: 
	point<double> a, b(2,2), p(1,1);
	bool onSegment = segDist(a,b,p) < 1e-10;
*/
#pragma once
#include "Point.h"

template <class P>
double segDist(const P& s, const P& e, const P& p) {
	if (s==e) return (p-s).dist();
	typedef typename P::coordType T;
	T d = (e-s).dist2(), t = min(d,max(T(0),(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}
