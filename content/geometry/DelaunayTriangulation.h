/**
 * Author: Mattias de Zalenski
 * Date: Unknown
 * Source: Geometry in C
 * Description: Computes the Delaunay triangulation of a set of points.
 *  Each circumcircle contains none of the input points.
 *  If any three points are colinear or any four are on the same circle, behavior is undefined.
 * Status: fuzz-tested
 * Time: O(n^2)
 */
#pragma once

#include "Point.h"
#include "3dHull.h"

template<class P, class F>
void delaunay(vector<P>& ps, F trifun) {
	if (sz(ps) == 3) { int d = (ps[0].cross(ps[1], ps[2]) < 0);
		trifun(0,1+d,2-d); }
	vector<P3> p3;
	trav(p, ps) p3.emplace_back(p.x, p.y, p.dist2());
	if (sz(ps) > 3) trav(t, hull3d(p3)) if ((p3[t.b]-p3[t.a]).
			cross(p3[t.c]-p3[t.a]).dot(P3(0,0,1)) < 0)
		trifun(t.a, t.c, t.b);
}
