/**
 * Author: Per Austrin
 * Date: 2004-02-08
 * License: CC0
 * Description: Finds the real roots to a polynomial.
 * Usage: vector<double> roots; polynomial p(2);
 p.a[0] = 2; p.a[1] = -3; p.a[2] = 1;
 poly_roots(p,-1e10,1e10,roots); // x^2-3x+2=0
 */
#pragma once

#include "Polynomial.h"

void poly_roots(const Polynomial& p, double xmin, double xmax, vector<double>& roots) {
	if (p.n == 1) { roots.push_back(-p.a.front()/p.a.back()); }
	else {
		Polynomial d = p;
		d.diff();
		vector<double> dr;
		poly_roots(d, xmin, xmax, dr);
		dr.push_back(xmin-1);
		dr.push_back(xmax+1);
		sort(all(dr));
		for (auto i = dr.begin(), j = i++; i != dr.end(); j = i++){
			double l = *j, h = *i, m, f;
			bool sign = p(l) > 0;
			if (sign ^ (p(h) > 0)) {
				//for(int i = 0; i < 60; ++i){
				while(h - l > 1e-8) {
					m = (l + h) / 2, f = p(m);
					if ((f <= 0) ^ sign) l = m;
					else h = m;
				}
				roots.push_back((l + h) / 2);
			}
		}
	}
}
