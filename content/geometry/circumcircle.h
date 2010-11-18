/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-11
 * Source: http://en.wikipedia.org/wiki/Circumcircle
 * Description:\\
\begin{minipage}{75mm}
The circumcirle of a triangle is the circle intersecting all three vertices. ccRadius returns the radius of the circle going through points A, B and C and ccCenter returns the center of the same circle. P is intended to be Point<double>.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{../content/geometry/circumcircle}
\end{minipage}
 * Status: tested
 * Usage:
 * 	Point<double> p1,p2,p3;
 * 	...
 * 	double radius = ccRadius(p1,p2,p3);
 * 	Point<double> center = ccCenter(p1,p2,p3);
 */
#pragma once
#include "Point.h"

template <class P>
double ccRadius(const P& A, const P& B, const P& C) {
	return (B-A).dist()*(C-B).dist()*(A-C).dist()/
			abs((B-A).cross(C-A))/2;
}

template <class P>
P ccCenter(const P& A, const P& B, const P& C) {
	P b = C-A, c = B-A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}
