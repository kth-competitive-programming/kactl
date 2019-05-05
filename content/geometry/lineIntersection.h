/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
If a unique intersection point of the lines going through s1,e1 and s2,e2 exists r is set to this point and 1 is returned. If no intersection point exists 0 is returned and if infinitely many exists -1 is returned. If s1==e1 or s2==e2 -1 is returned. The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates. Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * Status: tested
 * Usage:
 * 	point<double> intersection;
 * 	if (1 == LineIntersection(s1,e1,s2,e2,intersection))
 * 		cout << "intersection point at " << intersection << endl;
 */
#pragma once

#include "Point.h"

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1-s1).cross(e2-s2);
	if (d == 0)  //if parallel
		return {-((e1-s1).cross(s2-s1)==0 || s2==e2), P(0,0)};
	else
		return {1, s2-(e2-s2)*(e1-s1).cross(s2-s1)/d};
}
