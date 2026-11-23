/**
 * Author: chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://github.com/zimpha/algorithmic-library/blob/master/computational-geometry/polygon.cc
 * Description: Computes the intersection of a set of half-planes. Input is given as a set of planes, facing left.
 * Output is the convex polygon representing the intersection. The points may have duplicates and be collinear.
 * Will not fail catastrophically if `eps > sqrt(2)(line intersection error)`. Likely to work for more ranges if
 * 3 half planes are never guaranteed to intersect at the same point.
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
#define ang(a) (a[1] - a[0]).angle()

int angDiff(Line a, Line b) { return sgn(ang(a) - ang(b)); }
bool cmp(Line a, Line b) {
	int s = angDiff(a, b);
	return (s ? s : sideOf(sp(a), b[0])) < 0;
}
vector<P> halfPlaneIntersection(vector<Line> vs) {
	const double EPS = sqrt(2) * 1e-8;
	sort(all(vs), cmp);
	vector<Line> deq(sz(vs) + 5);
	vector<P> ans(sz(vs) + 5);
	deq[0] = vs[0];
	int ah = 0, at = 0, n = sz(vs);
	rep(i,1,n+1) {
		if (i == n) vs.push_back(deq[ah]);
		if (angDiff(vs[i], vs[i - 1]) == 0) continue;
		while (ah<at && sideOf(sp(vs[i]), ans[at-1], EPS) < 0)
			at--;
		while (i!=n && ah<at && sideOf(sp(vs[i]),ans[ah],EPS)<0)
			ah++;
		auto res = lineInter(sp(vs[i]), sp(deq[at]));
		if (res.first != 1) continue;
		ans[at++] = res.second, deq[at] = vs[i];
	}
	if (at - ah <= 2) return {};
	return {ans.begin() + ah, ans.begin() + at};
}
