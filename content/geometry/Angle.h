/**
 * Author: Simon Lindholm
 * Date: 2015-01-31
 * Source:
 * Description: A class for ordering angles (as represented by int points and
 *  a number of rotations around the origin). Useful for rotational sweeping.
 * Status: Works, used once
 */
#pragma once
#include <set>
#include <cassert>
using namespace std;

struct Angle {
	int x, y;
	int turn;
	Angle(int x, int y) : x(x), y(y), turn(0) { assert(x || y); }
	int quad() const {
		if (y < 0) return (x >= 0) + 2;
		if (y > 0) return (x <= 0);
		return (x <= 0) * 2;
	}
	Angle t90() const {
		Angle r = *this;
		if (quad() == 3) ++r.turn;
		r.x = -y;
		r.y = x;
		return r;
	}
	Angle t360() const { Angle r = *this; r.turn++; return r; }
};
bool operator<(const Angle& a, const Angle& b) {
	return make_tuple(a.turn, a.quad(), a.y * (ll)b.x) <
	       make_tuple(b.turn, b.quad(), a.x * (ll)b.y);
}

