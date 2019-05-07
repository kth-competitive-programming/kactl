/**
 * Author: Oleksandr Bacherikov, chilli
 * Date: 2019-05-07
 * License: CC0
 * Source:
 * Description: Line-convex polygon intersection. The polygon must be ccw and
 * have no colinear points. lineHull(line, poly) returns a pair representing
 * whether an intersection between the line and the hull occurs and a pair
 * describing the intersection.
 *  \begin{itemize*}
 *    \item $(i, -1)$ if touching the corner $i$,
 *    \item $(i, i)$ if along side $(i, i+1)$,
 *    \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$.
 *  \end{itemize*}
 *  In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$.
 *  The points are returned in the same order as the line hits the polygon.
 * Status: fuzz-tested
 * Time: O(N + Q \log n)
 */
#pragma once

#include "Point.h"
#include "lineIntersection.h"

typedef array<P, 2> Line;
#define isExtr(i) cmp(i+1, i) >= 0 && cmp(i, i-1) < 0
int extrVertex(vector<P> poly, P dir) {
	int n = sz(poly), l = 0, r = n;
	auto cmp = [&](int i, int j) {
		return sgn(dir.perp().cross(poly[(i + n) % n] - poly[(j + n) % n]));
	};
	if (isExtr(0)) return 0;
	while (l + 1 < r) {
		int m = (l + r) / 2;
		if (isExtr(m)) return m;
		int lS = cmp(l + 1, l), mS = cmp(m + 1, m);
		if (lS != mS ? lS < mS : lS == cmp(l, m)) r = m;
		else l = m;
	}
	return l;
}
pair<bool, array<int, 2>> lineHull(Line line, vector<P> poly) {
	array<int, 2> ends = {extrVertex(poly, (line[0] - line[1]).perp()),
	                      extrVertex(poly, (line[1] - line[0]).perp())};
	auto cmp = [&](int i) { return sgn(line[0].cross(poly[i], line[1])); };
	if (cmp(ends[0]) < 0 || cmp(ends[1]) > 0) return {};
	array<int, 2> res;
	for (int i = 0; i < 2; i++) {
		int l = ends[1], r = ends[0], n = sz(poly);
		while ((l + 1) % n != r) {
			int m = ((l + r + (l < r ? 0 : n)) / 2)%n;
			if (cmp(m) == cmp(ends[1])) l = m;
			else r = m;
		}
		res[i] = (l + (cmp(r) == 0)) % n;
		swap(ends[0], ends[1]);
	}
	if (res[0] == res[1]) res = {res[0], -1};
	else if (cmp(res[0]) == 0 && cmp(res[1]) == 0){
		if (res[0] - res[1] == 1 || res[1] - res[0] == sz(poly) - 1) res = {res[1], res[1]};
		else if (res[1] -res[0] == 1 || res[0] - res[1] == sz(poly) - 1) res = {res[0], res[0]};
	}
	return {true, res};
}
