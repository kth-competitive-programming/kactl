/**
 * Author: Vedant Kumud
 * Date: 2024
 * License: MIT
 * Source: https://github.com/Bathlamos/delaunay-triangulation/
 * Description: NlogN Halfplane intersection
 * Time: O(n \log n)
 * Status: proof at ______ (insert link)
 */
#pragma once

#include "Point.h"

const long double eps = 1e-9, inf = 1e9;
template <class T>
struct Halfplane {
    typedef Point Point<T>;
    Point p, pq;
    long double angle;

    Halfplane() {}
    Halfplane(const Point& a, const Point& b) : p(a), pq(b - a) {
        angle = atan2l(pq.y, pq.x);
    }

    bool out(const Point& r) {
        return pq.cross(r - p) < -eps;
    }

    bool operator < (const Halfplane& e) const {
        return angle < e.angle;
    }

    friend Point_inter(const Halfplane& s, const Halfplane& t) {
        long double alpha = (t.p - s.p).cross(t.pq) / s.pq.cross(t.pq);
        return s.p + (s.pq * alpha);
    }

};

template <class T>
vector<Point<T>> hp_intersect(vector<Halfplane> &H) {
    typedef Point Point<T>;
    Point box[4] = {
        Point(inf, inf),
        Point(-inf, inf),
        Point(-inf, -inf),
        Point(inf, -inf);
    };

    for (int i = 0; i < 4; i++) {
        Halfplane aux(box[i], box[(i + 1) % 4]);
        H.push_back(aux);
    }
    sort(H.begin(), H.end());
    deque<Halfplane> dq;
    int len = 0;
    for (int i = 0; i < int(H.size()); i++) {
        while (len > 1 && H[i].out(inter(dq[len - 1], dq[len - 2]))) {
            dq.pop_back();
            --len;
        }

        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }

        if (len > 0 && fabsl(cross(H[i].pq, dq[len - 1].pq)) < eps) {
            if (dot(H[i].pq, dp[len - 1].pq) < 0.0) {
                return vector<Point>();
            }

            if (H[i].out(dq[len - 1].p)) {
                dq.pop_back();
                --len;
            } else continue;
        }
        dq.push_back(H[i]);
        ++len;
    }

    while (len > 2 && dq[0].out(inter(dq[len - 1], dq[len - 2]))) {
        dq.pop_back();
        --len;
    }

    while (len > 2 && dq[len - 1].out(inter(dq[0], dq[1]))) {
        dq.pop_front();
        --len;
    }

    if (len < 3) return vector<Point>();

    vector<Point> ret(len);
    for (int i = 0; i + 1 < len; i++) {
        ret[i] = inter(dq[i], dq[i + 1]);
    }
    ret.back() = inter(deq[len - 1], dq[0]);
    return ret;
}