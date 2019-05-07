/**
 * Author: Tsinghua
 * Date: 2019-05-07
 * License:
 * Source: NAPC 2017 solution presentation
 * Description: Computes the minimum circle that encloses a set of points.
 * Time: expected O(n)
 * Status: fuzz-tested
 */
#pragma once

#include "circumcircle.h"

pair<double, P> minCircle(vector<P> ps) {
    shuffle(all(ps), mt19937(time(0)));
    int n = ps.size();
    P o = ps[0];
    double r = 0, EPS = (1 + 1e-8);
    rep(i, 1, n) if ((o - ps[i]).dist() > r * EPS) {
        o = ps[i], r = 0;
        rep(j, 0, i) if ((o - ps[j]).dist() > r * EPS) {
            o = (ps[i] + ps[j]) / 2;
            r = (o - ps[i]).dist();
            rep(k, 0, j) if ((o - ps[k]).dist() > r * EPS) {
                o = ccCenter(ps[i], ps[j], ps[k]);
                r = (o - ps[i]).dist();
            }
        }
    }
	return {r, o};
}
