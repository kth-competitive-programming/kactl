/**
 * Author: Simon Lindholm
 * Date: 2015-01-31
 * License: CC0
 * Source:
 * Description: A class for ordering angles (as represented by int points and
 *  a number of rotations around the origin). Useful for rotational sweeping.
 * Usage:
 *  vector<Angle> v = {w[0], w[0].t360() ...}; // sorted
 *  int j = 0; rep(i,0,n) {
 *    while (v[j] < v[i].t180()) ++j;
 *  } // sweeps j such that (j-i) represents the number of positively oriented triangles with vertices at 0 and i
 * Status: Used, works well
 */
#pragma once
#include <set>
#include <cassert>
using namespace std;

struct Angle {
	int x, y;
	int t;
	Angle(int x, int y, int t=0) : x(x), y(y), t(t) {}
	Angle operator-(Angle a) const { return {x-a.x, y-a.y, t}; }
	int quad() const {
		assert(x || y);
		if (y < 0) return (x >= 0) + 2;
		if (y > 0) return (x <= 0);
		return (x <= 0) * 2;
	}
	Angle t90() const { return {-y, x, t + (quad() == 3)}; }
	Angle t180() const { return {-x, -y, t + (quad() >= 2)}; }
	Angle t360() const { return {x, y, t + 1}; }
};
bool operator<(Angle a, Angle b) {
	// add a.dist2() and b.dist2() to also compare distances
	return make_tuple(a.t, a.quad(), a.y * (ll)b.x) <
	       make_tuple(b.t, b.quad(), a.x * (ll)b.y);
}
bool operator>=(Angle a, Angle b) { return !(a < b); }
bool operator>(Angle a, Angle b) { return b < a; }
bool operator<=(Angle a, Angle b) { return !(b < a); }

// Given two points, this calculates the smallest angle between
// them, i.e., the angle that covers the defined line segment.
pair<Angle, Angle> segmentAngles(Angle a, Angle b) {
	if (b < a) swap(a, b);
	return (b < a.t180() ?
	        make_pair(a, b) : make_pair(b, a.t360()));
}

Angle operator+(Angle a, Angle b) { // where b is a vector
	Angle r(a.x + b.x, a.y + b.y, a.t);
	if (r > a.t180()) r.t--;
	return r.t180() < a ? r.t360() : r;
}
