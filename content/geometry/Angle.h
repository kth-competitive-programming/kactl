/**
 * Author: Simon Lindholm
 * Date: 2015-01-31
 * Source:
 * Description: A class for ordering angles (as represented by int points and
 *  a number of rotations around the origin), plus some sample usages.
 *  Useful for rotational sweeping.
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
	int quad() const {
		assert(x || y);
		if (y < 0) return (x >= 0) + 2;
		if (y > 0) return (x <= 0);
		return (x <= 0) * 2;
	}
	Angle t90() const { return Angle(-y, x, t + (quad() == 3)); }
	Angle t180() const { return Angle(-x, -y, t + (quad()>=2)); }
	Angle t360() const { return Angle(x, y, t + 1); }
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

void sampleSweeping(const vector<pii>& points, int N) {
	rep(basei, 0, N) {
		vector<Angle> v;
		rep(i, 0, N) if (i != basei) {
			Angle a(points[i].first - points[basei].first,
			        points[i].second - points[basei].second);
			v.push_back(a);
			v.push_back(a.t360());
		}
		sort(all(v));
		int half = 0, res = 0;
		rep(i, 0, N-1) {
			// Count the number of points x in (v[i], v[i].rot(180))
			int m = 1;
			while (v[i+1] <= v[i]) ++i, ++m; // colinear points
			while (v[half] < v[i].t180()) ++half;
			res += m * (half - i - 1);
		}
		printf("%d\n", res);
	}
}
