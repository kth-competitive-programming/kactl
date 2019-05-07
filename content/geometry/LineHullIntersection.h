/**
 * Author: Johan Sannemo
 * Date: 2017-05-15
 * License: CC0
 * Source: thin air
 * Description: Line-convex polygon intersection. The polygon must be ccw and have no colinear points.
 *  isct(a, b) returns a pair describing the intersection of a line with the polygon:
 *  \begin{itemize*}
 *    \item $(-1, -1)$ if no collision,
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
    array<int, 2> ends = {extrVertex(poly, (line[0] - line[1]).perp()), extrVertex(poly, (line[1] - line[0]).perp())};
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
    return {true, res};
}