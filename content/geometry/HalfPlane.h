
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
#include "lineIntersection.h"

typedef Point<double> P;
typedef array<P, 2> Line;
#define sp(a) a[0], a[1]
#define ang(a) atan2((a[1] - a[0]).y, (a[1] - a[0]).x)
bool cmp(Line a, Line b) {
    auto s = ang(a) - ang(b);
    return s == 0 ? sideOf(sp(b), a[0]) >=0 : s < 0;
}
vector<P> halfPlaneIntersection(vector<Line> vs) {
    sort(all(vs), cmp);
    vector<Line> deq(sz(vs)+5);
    vector<P> ans(sz(vs)+5);
    int dh = 0, dt = 1, ah=0, at=0;
    deq[0] = vs[0];
    for (int i = 1; i < sz(vs); ++i) {
        if (ang(vs[i]) - ang(vs[i-1]) == 0) continue;
        while (ah < at && sideOf(sp(vs[i]), ans[at-1])< 0) at--, dt--;
        while (ah < at && sideOf(sp(vs[i]), ans[ah]) < 0) ah++, dh++;
        ans[at++] = lineInter(sp(deq[dt-1]), sp(vs[i])).second;
        deq[dt++] = vs[i];
    }
    while (ah < at && sideOf(sp(deq[dh]), ans[at-1]) < 0) at--, dt--;
    while (ah < at && sideOf(sp(deq[dt]), ans[ah]) < 0) ah++, dh++;
    if (dt-dh <= 2) return {};
    ans[at++] = lineInter(sp(deq[dh]), sp(deq[dt-1])).second;
    return {ans.begin()+ah, ans.begin()+at};
}