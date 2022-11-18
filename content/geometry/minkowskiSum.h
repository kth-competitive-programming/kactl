/**
 * Author: FHVirus
 * Date: 2022-11-18
 * License: CC0
 * Source: https://codeforces.com/contest/87/submission/181068924
 * Description: Output the minkowski sum for two convex hull. For distance of two convex hull A and B, calculate distance from O(0, 0) to minkowskiSum(A, -B).
 * Status: Tested with CodeForces 87E.
 */
#pragma once

#include "Point.h"
template<class P>
vector<P> minkowskiSum(vector<P> a, vector<P> b) {
	int n = sz(a), m = sz(b);
	rotate(begin(a), min_element(all(a)), end(a));
	rotate(begin(b), min_element(all(b)), end(b));
	a.push_back(a[0]); a.push_back(a[1]);
	b.push_back(b[0]); b.push_back(b[1]);
	vector<P> res;
	for (int i = 0, j = 0; i < n or j < m; ) {
		res.push_back(a[i] + b[j]);
		auto c = sgn((a[i+1] - a[i]).cross(b[j+1] - b[j]));
		i += (i < n and c >= 0);
		j += (j < m and c <= 0);
	}
	return res;
}
