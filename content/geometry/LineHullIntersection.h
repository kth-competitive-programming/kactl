/**
 * Author: Oleksandr Bacherikov, chilli
 * Date: 2019-05-07
 * License: CC0
 * Source:
 * Description: Line-convex polygon intersection. The polygon must be ccw and
 * have no colinear points. lineHull(line, poly) returns a pair describing the
 * intersection of a line with the polygon
 *  \begin{itemize*}
 *    \item $(-1, -1)$ if no collision,
 *    \item $(i, -1)$ if touching the corner $i$,
 *    \item $(i, i)$ if along side $(i, i+1)$,
 *    \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$.
 *  \end{itemize*}
 *  In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$.
 *  The points are returned in the same order as the line hits the polygon.
 * "extrVertex" returns the point of a hull with the max projection onto a line.
 * Status: fuzz-tested
 * Time: O(N + Q \log n)
 */
#pragma once

#include "Point.h"

typedef array<P, 2> Line;
#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
int extrVertex(vector<P>& poly, P dir) {
	int n = sz(poly), l = 0, r = n;
	if (extr(0)) return 0;
	while (l + 1 < r) {
		int m = (l + r) / 2;
		if (extr(m)) return m;
		int ls = cmp(l + 1, l), ms = cmp(m + 1, m);
		(ls < ms || (ls == ms && ls == cmp(l, m)) ? r : l) = m;
	}
	return l;
}

#define cmpL(i) sgn(line[0].cross(poly[i], line[1]))
array<int, 2> lineHull(Line line, vector<P> poly) {
	int endA = extrVertex(poly, (line[0] - line[1]).perp());
	int endB = extrVertex(poly, (line[1] - line[0]).perp());
	if (cmpL(endA) < 0 || cmpL(endB) > 0)
		return {-1, -1};
	array<int, 2> res;
	rep(i,0,2) {
		int l = endB, r = endA, n = sz(poly);
		while ((l + 1) % n != r) {
			int m = ((l + r + (l < r ? 0 : n)) / 2) % n;
			(cmpL(m) == cmpL(endB) ? l : r) = m;
		}
		res[i] = (l + !cmpL(r)) % n;
		swap(endA, endB);
	}
	if (res[0] == res[1]) return {res[0], -1};
	if (!cmpL(res[0]) && !cmpL(res[1]))
		switch ((res[0] - res[1] + sz(poly) + 1) % sz(poly)) {
			case 0: return {res[0], res[0]};
			case 2: return {res[1], res[1]};
		}
	return res;
}
