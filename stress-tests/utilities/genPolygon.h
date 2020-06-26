#pragma once

// Translated from Python code posted here: https://codeforces.com/blog/entry/63058?#comment-472788
// May generate polygons with colinear points. Won't generate polygons with duplicate points. No guarantee of the direction of the polygon.
#include "../../content/geometry/Point.h"
#include "../../content/geometry/PolygonArea.h"
#include "random.h"

template<class P> pair<bool, vector<P>> conquer(vector<P> pts, int depth) {
    if (depth>100) {
        return {false, {}};
    }
    if (sz(pts) <= 2) return {true,pts};
    if (sz(pts) == 3) {
        swap(pts[1], pts[2]);
        return {true,pts};
    }

    int divideId = randRange(2, sz(pts));
    P p1 = pts[divideId];
    double divideK = randDouble(0.01, 0.99);
    P p2(divideK*(pts[1].x-pts[0].x) + pts[0].x, divideK*(pts[1].y - pts[0].y) + pts[0].y);
    vector<double> line = {p2.y - p1.y, p1.x - p2.x, -p1.x*p2.y + p1.y*p2.x};
    int idx0 = ((line[0]*pts[0].x + line[1]*pts[0].y + line[2]) >=0);
    int idx1 = ((line[0]*pts[1].x + line[1]*pts[1].y + line[2]) >=0);
    if (idx0==idx1)
        return conquer(pts, depth+1);
    array<vector<P>, 2> S;
    S[idx0].push_back(pts[0]);
    S[idx0].push_back(p1);
    S[!idx0].push_back(p1);
    S[!idx0].push_back(pts[1]);
    rep(i,2,sz(pts)) {
        if (i == divideId) continue;
        int idx = ((line[0]*pts[i].x + line[1]*pts[i].y + line[2]) >=0);
        S[idx].push_back(pts[i]);
    }
    auto pa = conquer(S[idx0], depth+1);
    auto pb = conquer(S[!idx0], depth+1);
    if (!pa.first || !pb.first) return {false, {}};
    pb.second.erase(pb.second.begin());
    pa.second.insert(pa.second.end(), all(pb.second));
    return pa;
}
template<class P> vector<P> genPolygon(vector<P> pts, int depth=0) {
    if (depth>100) return {P(0,0), P(1,0), P(0,1)};
    sort(all(pts));
    pts.resize(unique(all(pts)) - pts.begin());
    shuffle_vec(pts);
    if (sz(pts) <=3) return pts;
    vector<double> line ={(double)(pts[1].y-pts[0].y), (double)(pts[0].x - pts[1].x), (double)(-pts[0].x*pts[1].y + pts[0].y*pts[1].x)};
    array<vector<P>, 2> S;
    S[0].push_back(pts[0]);
    S[0].push_back(pts[1]);
    S[1].push_back(pts[1]);
    S[1].push_back(pts[0]);
    rep(i,2,sz(pts)) {
        int idx = (line[0]*pts[i].x + line[1]*pts[i].y + line[2]) >=0;
        S[idx].push_back(pts[i]);
    }
    auto ta = conquer(S[0],0);
    auto tb = conquer(S[1],0);
    auto pa=ta.second, pb=tb.second;
    if (!ta.first || !tb.first) {
        return genPolygon(pts, depth+1);
    }
    pa.erase(pa.begin());
    pb.erase(pb.begin());
    pa.insert(pa.end(), all(pb));
    if (polygonArea2(pa) < 0) reverse(all(pa));
    return pa;
}
