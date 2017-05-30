/**
 * Author: Johan Sannemo
 * Date: 2017-05-15
 * License: CC0
 * Source: thin air
 * Description: Line-convex polygon intersection. The polygon must be ccw and have no colinear points.
 *  isct(a, b) returns a pair describing the intersection of a line with the polygon:
 *  \begin{itemize*}
 *    \item $(-1, -1)$ if no collision,
 *    \item $(i, -1)$ if touching the corner $i$,
 *    \item $(i, i)$ if along side $(i, i+1)$,
 *    \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$.
 *  \end{itemize*}
 *  In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$.
 *  The points are returned in the same order as the line hits the polygon.
 * Status: fuzz-tested
 * Time: O(N + Q \log n)
 */
#pragma once

#include "Point.h"

ll sgn(ll a) { return (a > 0) - (a < 0); }
typedef Point<ll> P;
struct HullIntersection {
	int N;
	vector<P> p;
	vector<pair<P, int>> a;

	HullIntersection(const vector<P>& ps) : N(sz(ps)), p(ps) {
		p.insert(p.end(), all(ps));
		int b = 0;
		rep(i,1,N) if (P{p[i].y,p[i].x} < P{p[b].y, p[b].x}) b = i;
		rep(i,0,N) {
			int f = (i + b) % N;
			a.emplace_back(p[f+1] - p[f], f);
		}
	}

	int qd(P p) {
		return (p.y < 0) ? (p.x >= 0) + 2
		     : (p.x <= 0) * (1 + (p.y <= 0));
	}

	int bs(P dir) {
		int lo = -1, hi = N;
		while (hi - lo > 1) {
			int mid = (lo + hi) / 2;
			if (make_pair(qd(dir), dir.y * a[mid].first.x) <
				make_pair(qd(a[mid].first), dir.x * a[mid].first.y))
				hi = mid;
			else lo = mid;
		}
		return a[hi%N].second;
	}

	bool isign(P a, P b, int x, int y, int s) {
		return sgn(a.cross(p[x], b)) * sgn(a.cross(p[y], b)) == s;
	}

	int bs2(int lo, int hi, P a, P b) {
		int L = lo;
		if (hi < lo) hi += N;
		while (hi - lo > 1) {
			int mid = (lo + hi) / 2;
			if (isign(a, b, mid, L, -1)) hi = mid;
			else lo = mid;
		}
		return lo;
	}

	pii isct(P a, P b) {
		int f = bs(a - b), j = bs(b - a);
		if (isign(a, b, f, j, 1)) return {-1, -1};
		int x = bs2(f, j, a, b)%N,
		    y = bs2(j, f, a, b)%N;
		if (a.cross(p[x], b) == 0 &&
		    a.cross(p[x+1], b) == 0) return {x, x};
		if (a.cross(p[y], b) == 0 &&
		    a.cross(p[y+1], b) == 0) return {y, y};
		if (a.cross(p[f], b) == 0) return {f, -1};
		if (a.cross(p[j], b) == 0) return {j, -1};
		return {x, y};
	}
};
