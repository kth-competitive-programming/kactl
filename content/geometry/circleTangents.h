/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-06
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
Returns a pair of the two points on the circle with radius r centered around c whos tangent lines intersect p. If p lies within the circle NaN-points are returned. P is intended to be Point<double>. The first point is the one to the right as seen from the p towards c.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{../content/geometry/circleTangents}
\end{minipage}
 * Status: tested
 * Usage:
 * 	typedef Point<double> P;
 * 	pair<P,P> p = circleTangents(P(100,2),P(0,0),2);
 */
#pragma once

#include "Point.h"

template<class P>
pair<P,P> circleTangents(const P &p, const P &c, double r) {
	P a = p-c;
	double x = r*r/a.dist2(), y = sqrt(x-x*x);
	return make_pair(c+a*x+a.perp()*y, c+a*x-a.perp()*y);
}
