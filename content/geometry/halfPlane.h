
/**
 * Author:
 * Date:
 * License:
 * Source:
 * Description:
 * Time:
 * Status:
 * Usage:
 */
#pragma once

#include "Point.h"
#include "sideOf.h"

typedef Point<double> P;
typedef array<P, 2> Line;
#define v(a) (a[1] - a[0])
#define c(a) (v(a).cross(a[0]))
pair<int, P> lineInter(Line a, Line b) {
	auto d = v(a).cross(v(b));
	if (d == 0) return {-(c(a) == c(b)), P(0,0)};
	else return {1, (v(b)*c(a) - v(a)*c(b))/d};
}

#define ang(a) atan2(v(a).y, v(a).x)
int sideOf(Line l, P p) {return sideOf(l[0], l[1], p);}
vector<P> halfPlaneIntersection(vector<Line> vs) {
    sort(all(vs), [](auto a, auto b) { return ang(a) < ang(b);});
    vs.resize(unique(all(vs), [](auto a, auto b){ return ang(a) == ang(b);}) - vs.begin());
    deque<Line> deq({vs[0]});
    deque<P> ans;
    for (int i = 1; i < sz(vs); ++i) {
        if (sgn(ang(vs[i]) - ang(vs[i-1])) == 0) continue;
        while (sz(ans) && sideOf(vs[i], ans.back())< 0)
            ans.pop_back(), deq.pop_back();
        while(sz(ans) && sideOf(vs[i], ans.front()) < 0)
            ans.pop_front(), deq.pop_front();
        ans.push_back(lineInter(deq.back(), vs[i]).second);
        deq.push_back(vs[i]);
    }
    while (sz(ans) && sideOf(deq.front(), ans.back()) < 0)
        ans.pop_back(), deq.pop_back();
    while (sz(ans) && sideOf(deq.back(), ans.front()) < 0)
        ans.pop_front(), deq.pop_front();
    if (sz(deq) <= 2) return {};
    ans.push_back(lineInter(deq.front(), deq.back()).second);
    return vector<P>(all(ans));
}