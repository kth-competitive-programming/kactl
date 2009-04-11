/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * Source:
 * Description: Returns where $p$ is as seen from $s$ towards $e$. 1/0/-1 $\Leftrightarrow$ left/on line/right. If the optional argument $epsilon$ is given 0 is returned if $p$ is within distance $epsilon$ from the line. P is supposed to be Point<T> where T is e.g. double or long long. It uses products in intermediate steps so watch out for overflow if using int or long long.
 * Status: tested
 * Usage:
 * 	bool left = sideOf(p1,p2,q)==1;
 */
#pragma once
#include "Point.h"

template <class P>
int sideOf(const P& s, const P& e, const P& p) {
	typename P::coordType a = (e-s).cross(p-s);
	return (a > 0) - (a < 0);
}

template <class P>
int sideOf(const P& s, const P& e, const P& p, double epsilon) {
	typename P::coordType a = (e-s).cross(p-s);
	double l = (e-s).dist()*epsilon;
	return (a > l) - (a < -l);
}
