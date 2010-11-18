/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-04
 * Source: Basic algorithm knowledge
 * Description:
\\\begin{minipage}{75mm}
Rearanges the points between begin and end so that the points of the hull are in counterclockwise order between begin and the returned iterator. Points on the edge of the hull between two other points are not considered part of the hull.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{../content/geometry/convexHull}
\end{minipage}
 * Status: tested with unitTest and Kattis problems convexhull, copsrobbers and centerofmass
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

//change to use other types of points
typedef Point<double> ptype;
ptype ref;
bool comp(const ptype &p, const ptype &q) {
	return (p-ref).cross(q-p)>0 ||
			(p-ref).cross(q-p)==0 && (p-ref).dist2()<(q-ref).dist2();
}

template <class It>
It convexHull(It begin, It end) {
	//zero or one point always form a hull
	if (end-begin < 2) return end;
	//find a guaranteed hull point to use as origo
	ref = *min_element(begin,end);
	sort(begin, end, comp); //sort in scan order
	//place hull points first by doing a Graham scan
	It r = begin + 1;
	for (It i = begin+2; i != end; ++i) {
		while (r > begin && (*r-*(r-1)).cross(*i-*r) <= 0) --r;
		swap(*++r, *i);
	}
	if (r-begin == 1 && *begin == *r) r--;
	return ++r; //return the iterator past the last hull point
}
