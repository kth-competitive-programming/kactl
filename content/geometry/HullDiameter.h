/**
 * Author: Johan Sannemo
 * Date: 2017-03-12
 * License: CC0
 * Source: Wikipedia
 * Description: Calculates the max squared distance of a set of points.
 * Works with integers.
 * Status: Tested.
 */
#pragma once

#include "ConvexHull.h"

array<P, 2> hullDiameter(vector<P> S) {
	int n = sz(S), j = n < 2 ? 0 : 1;
	pair<ll, array<P, 2>> res;
	rep(i,0,j)
		for (;; j = (j + 1) % n) {
			res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
			if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
				break;
		}
	return res.second;
}
