/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: NAPC 2017 solution presentation
 * Description: Computes the minimum circle that encloses a set of points.
 * Time: expected O(n)
 * Status: fuzz-tested
 */
#pragma once

#include "circumcircle.h"

pair<double, P> mec2(vector<P>& S, P a, P b, int n) {
	double hi = INFINITY, lo = -hi;
	rep(i,0,n) {
		auto si = (b-a).cross(S[i]-a);
		if (si == 0) continue;
		P m = ccCenter(a, b, S[i]);
		auto cr = (b-a).cross(m-a);
		if (si < 0) hi = min(hi, cr);
		else lo = max(lo, cr);
	}
	double v = (0 < lo ? lo : hi < 0 ? hi : 0);
	P c = (a + b) / 2 + (b - a).perp() * v / (b - a).dist2();
	return {(a - c).dist2(), c};
}
pair<double, P> mec(vector<P>& S, P a, int n) {
	random_shuffle(S.begin(), S.begin() + n);
	P b = S[0], c = (a + b) / 2;
	double r = (a - c).dist2();
	rep(i,1,n) if ((S[i] - c).dist2() > r * (1 + 1e-8)) {
		tie(r,c) = (n == sz(S) ?
			mec(S, S[i], i) : mec2(S, a, S[i], i));
	}
	return {r, c};
}
pair<double, P> enclosingCircle(vector<P> S) {
	assert(!S.empty()); auto r = mec(S, S[0], sz(S));
	return {sqrt(r.first), r.second};
}
