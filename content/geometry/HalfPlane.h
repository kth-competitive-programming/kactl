
/**
 * Author: chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://github.com/zimpha/algorithmic-library/blob/master/computational-geometry/polygon.cc
 * Description: Computes the intersection of a set of half-planes.
 * Time: O(n \log n)
 * Status: fuzz-tested, submitted on https://maps19.kattis.com/problems/marshlandrescues
 * Usage:
 */
#pragma once

#include "Point.h"
#include "sideOf.h"
#include "lineIntersection.h"

typedef Point<double> P;
typedef array<P, 2> Line;
#define sp(a) a[0], a[1]
#define ang(a) atan2((a[1] - a[0]).y, (a[1] - a[0]).x)

int angDiff(Line a, Line b) { return sgn(ang(a) - ang(b)); }
bool cmp(Line a, Line b) {
	auto s = angDiff(a, b);
	return s == 0 ? sideOf(sp(b), a[0]) >= 0 : s < 0;
}
vector<P> halfPlaneIntersection(vector<Line> vs) {
	sort(all(vs), cmp);
	vector<Line> deq(sz(vs) + 5);
	vector<P> ans(sz(vs) + 5);
	deq[0] = vs[0];
	int dh = 0, dt = 1, ah = 0, at = 0;
    #define upd(l, pt, op) while (ah < at && sideOf(sp(l), ans[pt]) < 0) op;
	for (int i = 1; i < sz(vs); ++i) {
		if (angDiff(vs[i], vs[i - 1]) == 0) continue;
        upd(vs[i], at-1, (at--,dt--)) upd(vs[i], ah, (ah++,dh++));
		ans[at++] = lineInter(sp(deq[dt - 1]), sp(vs[i])).second;
		deq[dt++] = vs[i];
	}
    upd(deq[dh], at-1, (at--,dt--)); upd(deq[dt], ah, (ah++,dh++));
	if (dt - dh <= 2) return {};
	ans[at++] = lineInter(sp(deq[dt-1]), sp(deq[dh])).second;
	return {ans.begin() + ah, ans.begin() + at};
}
