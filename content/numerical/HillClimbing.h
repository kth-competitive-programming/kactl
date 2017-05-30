/**
 * Author: Simon Lindholm
 * Date: 2015-02-04
 * License: CC0
 * Source: Johan Sannemo
 * Description: Poor man's optimization for unimodal functions.
 * Status: used with great success
 */
#pragma once

typedef array<double, 2> P;

double func(P p);

pair<double, P> hillClimb(P start) {
	pair<double, P> cur(func(start), start);
	for (double jmp = 1e9; jmp > 1e-20; jmp /= 2) {
		rep(j,0,100) rep(dx,-1,2) rep(dy,-1,2) {
			P p = cur.second;
			p[0] += dx*jmp;
			p[1] += dy*jmp;
			cur = min(cur, make_pair(func(p), p));
		}
	}
	return cur;
}
