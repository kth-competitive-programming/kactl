/**
 * Author: Stjepan Glavina, chilli
 * Date: 2019-05-05
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * Description:
\\\begin{minipage}{75mm}
Returns a vector of the points of the convex hull in counter-clockwise order.
Points on the edge of the hull between two other points are not considered part of the hull.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Time: O(n \log n)
 * Status: stress-tested, tested with kattis:convexhull
*/
#include <vector>
#pragma once
#include "Point.h"

template<class T>
std::vector<Point<T>> convexHull(std::vector<Point<T>> pts) {
	using P = Point<T>;
	if ((int) pts.size() <= 1) return pts;
	sort(pts.begin(), pts.end());
	std::vector<P> h((int) pts.size()+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
