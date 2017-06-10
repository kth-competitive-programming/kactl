/**
 * Author: Johan Sannemo
 * Date: 2017-04-13
 * License: CC0
 * Source: Inspired by old, broken tinyKACTL
 * Description: Determine whether a point t lies inside a given polygon (counter-clockwise order).
 * The polygon must be such that every point on the circumference is visible from the first point in the vector.
 * It returns 0 for points outside, 1 for points on the circumference, and 2 for points inside.
 * Usage:
 * Status: Tested at Moscow ICPC pre-finals workshop
 * Time: O(\log N)
 */
#pragma once

#include "Point.h"
#include "sideOf.h"
#include "onSegment.h"

typedef Point<ll> P;
int insideHull2(const vector<P>& H, int L, int R, const P& p) {
	int len = R - L;
	if (len == 2) {
		int sa = sideOf(H[0], H[L], p);
		int sb = sideOf(H[L], H[L+1], p);
		int sc = sideOf(H[L+1], H[0], p);
		if (sa < 0 || sb < 0 || sc < 0) return 0;
		if (sb==0 || (sa==0 && L == 1) || (sc == 0 && R == sz(H)))
			return 1;
		return 2;
	}
	int mid = L + len / 2;
	if (sideOf(H[0], H[mid], p) >= 0)
		return insideHull2(H, mid, R, p);
	return insideHull2(H, L, mid+1, p);
}

int insideHull(const vector<P>& hull, const P& p) {
	if (sz(hull) < 3) return onSegment(hull[0], hull.back(), p);
	else return insideHull2(hull, 1, sz(hull), p);
}
