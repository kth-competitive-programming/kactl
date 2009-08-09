/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-04
 * Source: Basic algorithm knowledge
 * Description: Rearanges the points between begin and end so that the points of the hull are in counterclockwise order between begin and the returned iterator. Points on the edge of the hull between two other points are not considered part of the hull.
 * Status: tested (with unitTest and Kattis convexhull)
 * Usage:
 * 	vector<Point<double> > p;
 * 	vector<Point<double> >
 				hull(p.begin(),convexHull(p.begin(),p.end()));
 * 	p.resize(convexHull(p.begin(),p.end())-p.begin());
 * Time: O(n)
*/
#pragma once
#include <algorithm>
#include "Point.h"

template <class P>
bool comp(const P &p, const P &q) {
	return p.cross(q)>0 || p.cross(q)==0 && p.dist2()<q.dist2();
}

template <class It>
It convexHull(It begin, It end) {
	typedef typename iterator_traits<It>::value_type T;
	//zero or one point always form a hull
	if (end-begin < 2) return end;
	//find a guaranteed hull point to use as origo
	T ref = *min_element(begin,end);
	for (It i = begin; i != end; ++i) *i = *i-ref;
	sort(begin, end, comp<T>); //sort in scan order
	//place hull points first by doing a Graham scan
	It r = begin + 1;
	for (It i = begin+2; i != end; ++i) {
		while (r > begin && (*r-*(r-1)).cross(*i-*(r-1)) <= 0)
			--r;
		swap(*++r, *i);
	}
	for (It i = begin; i != end; ++i) *i = *i+ref;
	if (r-begin == 1 && *begin == *r) r--;
	//return the iterator past the last hull point
	return ++r;
}
