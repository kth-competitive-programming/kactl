/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-27
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
If a unique intersection point between the line segments going from s1 to e1 and from s2 to e2 exists then it is returned.
If no intersection point exists an empty vector is returned. If infinitely many exist a vector with 2 elements is returned.
The wrong position will be returned if P is Point<int> and the intersection point does not have integer coordinates.
Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Status: Well tested with fuzz-test and with Kattis problem intersection.
 * Usage:
 * vector<P> inter = segInter(s1,e1,s2,e2);
 * if (inter.size()==1)
 *   cout << "segments intersect at " << inter[0] << endl;
 */
#pragma once

#include "Point.h"
#include "onSegment.h"

template <class P> bool segInterProper(P a, P b, P c, P d,
										P &out) {
	double oa = c.cross(d, a), ob = c.cross(d, b),
		   oc = a.cross(b, c), od = a.cross(b, d);
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
		out = (a * ob - b * oa) / (ob - oa);
		return true;
	}
	return false;
}
template<class P> vector<P> segInter(P a, P b, P c, P d) {
	P out;
	if (segInterProper(a, b, c, d, out)) return {out};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return vector<P>(all(s));
}
