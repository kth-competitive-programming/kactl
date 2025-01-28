/**
 * Author: Tyler Marks
 * Date: 2025-01-25
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
 * Status: tested
*/
#pragma once

#include "Point.h"

template<class P> vector<P> convex_hull(vector<P> pts){
	if(sz(pts) == 1) return pts;
	stable_sort(all(pts));
	vector<P> hull(sz(pts)+1);
	int k = 0, t = 2;
	rep(_, 0, 2) {
		for(P p: pts){
			while(k >= t && hull[k-2].cross(hull[k-1], p) <= 0) k--;
			hull[k++] = p;
		}
		reverse(all(pts));
		t = k+1;
	}
	hull.resize(k-1);
	return hull;
}