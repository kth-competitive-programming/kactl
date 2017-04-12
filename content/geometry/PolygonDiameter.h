/**
 * Author: Johan Sannemo
 * Date: 2017-03-12
 * Source: Wikipedia
 * Description: Calculates the max distance^2 of a set of points.
 * Status: Tested.
 */
#pragma once
#include <vector>
#include "Point.h"
using namespace std;

typedef Point<ll> P;
ll polygonDiameter(vector<P> points) {
    sort(all(points));
    vector<P> U, L;
    trav(it, points) {
        while (sz(U) > 1 && U[sz(U)-2].cross(it, U.back()) <= 0) U.pop_back();
        while (sz(L) > 1 && L[sz(L)-2].cross(it, L.back()) >= 0) L.pop_back();
        U.push_back(it);
        L.push_back(it);
    }
    vector<pair<P, P>> antipodal;
    int i = 0;
    int j = sz(L) - 1;
    while (i < sz(U) - 1 || j > 0) {
        antipodal.emplace_back(U[i], L[j]);
        if (i == sz(U) - 1) --j;
        else if (j == 0) ++i;
        else if ((U[i+1].y - U[i].y) * (L[j].x - L[j-1].x) > (U[i+1].x - U[i].x) * (L[j].y - L[j-1].y)) ++i;
        else --j;
    }
    ll ans = 0;
    trav(it, antipodal) ans = max(ans, (it.first - it.second).dist2());
    return ans;
}
