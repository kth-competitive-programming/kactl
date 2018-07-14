/**
 * Author: Ulf Lundstrom, Simon Lindholm
 * Date: 2016-09-24
 * License: CC0
 * Source: SegmentIntersection.h
 * Description: Like segmentIntersection, but only returns true/false.
 * Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
 * Status: Relatively well tested.
 */
#pragma once

#include "Point.h"

template<class P>
bool segmentIntersectionQ(P s1, P e1, P s2, P e2) {
	if (e1 == s1) {
		if (e2 == s2) return e1 == e2;
		swap(s1,s2); swap(e1,e2);
	}
	P v1 = e1-s1, v2 = e2-s2, d = s2-s1;
	auto a = v1.cross(v2), a1 = d.cross(v1), a2 = d.cross(v2);
	if (a == 0) { // parallel
		auto b1 = s1.dot(v1), c1 = e1.dot(v1),
		     b2 = s2.dot(v1), c2 = e2.dot(v1);
		return !a1 && max(b1,min(b2,c2)) <= min(c1,max(b2,c2));
	}
	if (a < 0) { a = -a; a1 = -a1; a2 = -a2; }
	return (0 <= a1 && a1 <= a && 0 <= a2 && a2 <= a);
}
