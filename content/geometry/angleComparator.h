/**
 * Author: Simon Lindholm
 * Date: 2015-01-31
 * Source:
 * Description: Comparator of points, for angles around a base point. Angles are counter-clockwise starting from the right.
 *  Products of two coordinate differences are used in intermediate steps, so only use if coordinates are <= 1e9.
 * Status: tested
 */
#pragma once
#include "Point.h"
#include <set>
#include <cassert>
using namespace std;

struct AngleComp {
	typedef Point<long long> P;
	P around;
	AngleComp(P a) : around(a) {}
	template<class T>
	int quad(const T& p) const {
		if (p.y < 0) return (p.x >= 0) + 2;
		if (p.y > 0) return (p.x <= 0);
		assert(p.x);
		return (p.x <= 0) * 2;
	}
	bool operator()(P a, P b) const {
		a = a - around;
		b = b - around;
		return make_pair(quad(a), a.y * b.x) <
		       make_pair(quad(b), a.x * b.y);
	}
};
