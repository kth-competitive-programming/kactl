/**
* Author:
* Date: 2010-11-18
* Source: tinyKACTL
* Description:
*/
#pragma once

#include <vector>
#include "polynomial.h"
using namespace std;

const double eps = 1e-8;

void poly_roots(const polynomial& p, double xmin, double xmax, vector<double>& roots) {
	if (p.n == 1) { roots.push_back(-p.a.front()/p.a.back()); }
	else {
		polynomial d = p;
		vector<double> droots;
		d.diff();
		poly_roots(d, xmin, xmax, droots);
		droots.push_back(xmin-1);
		droots.push_back(xmax+1);
		sort(droots.begin(), droots.end());
		for (vector<double>::iterator i = droots.begin(), j = i++; i != droots.end(); j = i++) {
			double l = *j, h = *i, m, f;
			bool sign = p(l) > 0;
			if (sign ^ p(h) > 0) {
				while(h - l > eps) {
					m = (l + h) / 2, f = p(m);
					if (f <= 0 ^ sign) l = m;
					else h = m;
				}
				roots.push_back((l + h) / 2);
			}
		}
	}
}
