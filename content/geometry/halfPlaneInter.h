/**
 * Author: FHVirus
 * Date: 2022-11-18
 * License: CC0
 * Source: cheissmart
 * Description: Given n segments (s, t), return the polygon of the area of the intersection of the left of the n segments.
 * Status: Tested with Big Brother on Kattis.
 */
#pragma once

#include "Point.h"
#include "sideOf.h"

typedef Point<double> P;
typedef pair<P, P> S;
P interp(const S& a, const S& b) {
	double ax = (a.second - a.first).cross(b.first - a.first);
	double ay = (b.second - a.first).cross(a.second - a.first);
	return (b.first * ay + b.second * ax) / (ax + ay);
}
bool cmp(const S& a, const S& b) {
	static const P o(0, 0);
	P va = a.second - a.first, vb = b.second - b.first;
	if (sgn(va.cross(vb)) == 0 and sgn(va.dot(vb)) >= 0)
		return sideOf(b.first, b.second, a.first) > 0;
	bool ba = (o < va), bb = (o < vb);
	if (ba xor bb) return ba > bb;
	return sgn(va.cross(vb)) > 0;
}
vector<P> halfPlaneInter(vector<S> ss) {
	int n = sz(ss), qh = 0, qt = 0;
	sort(all(ss), cmp);
	vector<P> in(n);
	vector<S> dq(n);
	rep (i, 0, n) {
		while (qt - qh > 1 and sideOf(ss[i].first, ss[i].second, in[qt - 2]) <= 0) --qt;
		while (qt - qh > 1 and sideOf(ss[i].first, ss[i].second, in[qh]) <= 0) ++qh;
		dq[qt++] = ss[i];
		if (qt - qh > 1) in[qt - 2] = interp(dq[qt - 2], dq[qt - 1]);
	}
	while (qt - qh > 1 and sideOf(dq[qh].first, dq[qh].second, in[qt - 2]) <= 0) --qt;
	in[qt - 1] = interp(dq[qh], dq[qt - 1]);
	return {begin(in) + qh, begin(in) + qt};
}
