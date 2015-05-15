/**
 * Author: Unknown
 * Date: Unknown
 * Source: tinyKACTL
 * Description: Computes a Delauney triangulation of a set of points. It has the property that each circumcircle contains none of the input points.
 If any four are on the same circle, the triangulation is not unique.
 If \emph{all} are on the same circle, \emph{the algorithm will fail} -- this case may need to be treated specially.
 If some three are on the same line, there is no telling what the algorithm will do. Warning; untested.
 * Usage:
 * Status: not tested
 * Time: O(n^2)
 */
#include "3dHull.h"

template <class V, class F>
void delaunay(V &p, F trifun) {
	vector<P3> p3(sz(p));
	rep(i,0,sz(p))
		p3[i] = P3(p[i].x, p[i].y, p[i].dist2());
	list<ABC> l;
	convex_hull_space(p3, l);
	trav(t, l) if ((p3[t.b]-p3[t.a]).
			cross(p3[t.c]-p3[t.a]).dot(P3(0,0,1)) < 0)
		trifun(t.a, t.c, t.b); // triangles are turned!
}
