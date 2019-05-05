/**
 * Author: Johan Sannemo
 * Date: 2017-04-16
 * License: CC0
 * Source: Basic algorithm knowledge
 * Description:
\\\begin{minipage}{75mm}
Returns a vector of indices of the convex hull in counter-clockwise order.
Points on the edge of the hull between two other points are not considered part of the hull.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Status: tested with Kattis problems convexhull
 * Usage:
 * 	vector<P> ps, hull;
 *  trav(i, convexHull(ps)) hull.push_back(ps[i]);
 * Time: O(n \log n)
*/
#pragma once

#include "Point.h"

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int t = 0;
	rep(it,0,2) {
		auto s = t;
		for (auto &p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
		t--, reverse(all(pts));
	}
	if (t == 2 && h[0] == h[1]) t--;
	return {h.begin(), h.begin()+t};
}