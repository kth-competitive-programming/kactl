/**
 * Author: chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://github.com/zimpha/algorithmic-library/blob/master/computational-geometry/polygon.cc
 * Description: Computes the intersection of a set of half-planes. Input is given as a set of planes, facing left.
 * Output is the convex polygon representing the intersection. The points may have duplicates and be collinear.
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
	// for (auto l: vs) {
	// 	cout<<l[0]<<" -> "<<l[1]<<endl;
	// }
	vector<Line> deq(sz(vs) + 5);
	vector<P> ans(sz(vs) + 5);
	deq[0] = vs[0];
	int ah = 0, at = 0, n = sz(vs);
	rep(i,1,n+1) {
		if (i == n) vs.push_back(deq[ah]);
		if (angDiff(vs[i], vs[i - 1]) == 0) {
			continue;
		}

		while (ah<at && sideOf(sp(vs[i]),ans[at-1], 1e-8) < 0) at--;
		while (i!=n && ah<at && sideOf(sp(vs[i]),ans[ah], 1e-8)<0) ah++;
		auto res = lineInter(sp(vs[i]), sp(deq[at]));
		if (res.first != 1) {
			// cout<<"46"<<endl;
			continue;
		}
		ans[at++] = res.second, deq[at] = vs[i];
		// cout<<"i: "<<i<<endl;
		// cout<<"ans: ";
		// cout<<ah<<' '<<at<<endl;
		// for (int j=ah; j<at; j++) {
		// 	cout<<ans[j]<<" ";
		// }
		// cout<<endl;
		// cout<<"deq: ";
		// for(int j=ah; j<=at; j++) {
		// 	cout<<deq[j][0]<<"-> "<<deq[j][1]<<' ';
		// }
		// cout<<endl;
		// cout<<endl;
	}
	if (at - ah <= 2) return {};
	return {ans.begin() + ah, ans.begin() + at};
}
