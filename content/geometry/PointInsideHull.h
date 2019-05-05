/**
 * Author: chilli
 * Date: 2019-05-17
 * License: CC0
 * Source: https://github.com/ngthanhtrung23/ACM_Notebook_new
 * Description: Determine whether a point t lies inside a convex hull. Returns
 * true if point lies strictly within the hull. Returns !strict if point lies
 * on the boundary.
 * Usage:
 * Status: fuzz-tested
 * Time: O(\log N)
 */
#pragma once

#include "Point.h"
#include "onSegment.h"

typedef Point<ll> P;

bool inHull(const vector<P> &l, P p, bool strict = true) {
    int a = 1, b = l.size() - 1, r = !strict;
	if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
    if (l[0].cross(l[a], l[b]) > 0) swap(a, b);
    if (sgn(l[0].cross(l[a], p)) >= r ||
        sgn(l[0].cross(l[b], p)) <= -r) return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (l[0].cross(l[c], p) > 0 ? b : a)  = c;
    }
    return !(sgn(l[a].cross(l[b], p)) >= r);
}
