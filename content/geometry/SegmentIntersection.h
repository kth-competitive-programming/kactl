/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
If a unique intersetion point between the line segments going from s1 to e1 and from s2 to e2 exists r1 is set to this point and 1 is returned.
If no intersection point exists 0 is returned and if infinitely many exists 2 is returned and r1 and r2 are set to the two ends of the common line.
The wrong position will be returned if P is Point<int> and the intersection point does not have integer coordinates.
Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
Use segmentIntersectionQ to get just a true/false answer.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{../content/geometry/SegmentIntersection}
\end{minipage}
 * Status: Well tested with unitTest and with Kattis problem intersection.
 * Usage:
 * Point<double> intersection, dummy;
 * if (segmentIntersection(s1,e1,s2,e2,intersection,dummy)==1)
 *   cout << "segments intersect at " << intersection << endl;
 */
#pragma once

#include "Point.h"
#include "onSegment.h"
#include "SegmentIntersectionProper.h"

template<class P> set<P> segInter(P a, P b, P c, P d) {
    P out;
    if (segInterProper(a, b, c, d, out)) return {out};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return s;
}