/**
 * Author: marks39, Meaf, lightseba
 * Date: 2023-02-10
 * Description: Finds the left and right, respectively, tangent 
 * points on convex hull from a point. If the point is colinear 
 * to side(s) of the polygon, the point further away is 
 * returned. Requires ccw, $n \geq 3$, and the point be on or 
 * outside the polygon. Can be used to check if a point is inside
 * of a convex hull. Will return -1 if it is strictly inside. If
 * the point is on the hull, the two adjacent points will be returned
 * Time: O(\log n)
 * Status: tested on ASC 40: A and SER 2016: D
 */
#pragma once
#include "Point.h"
#define cmp(i, j) p.cross(h[i], h[j == n ? 0 : j]) * (R ? 1 : -1)
template<bool R, class P> int getTangent(vector<P>& h, P p) {
	int n = sz(h), lo = 0, hi = n - 1, md;
	if (cmp(0, 1) >= R && cmp(0, n - 1) >= !R) return 0;
	while (md = (lo + hi + 1) / 2, lo < hi) {
		auto a = cmp(md, md + 1), b = cmp(md, lo);
		if (a >= R && cmp(md, md - 1) >= !R) return md;
		if (cmp(lo, lo + 1) < R)
			a < R&& b >= 0 ? lo = md : hi = md - 1;
		else a < R || b <= 0 ? lo = md : hi = md - 1;
	}
	return -1; // point strictly inside hull
}
template<class P> pii hullTangents(vector<P>& h, P p) {
	return {getTangent<0>(h, p), getTangent<1>(h, p)};
}