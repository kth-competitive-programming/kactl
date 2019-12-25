#pragma once

#include <bits/stdc++.h>
#include "../../content/geometry/Point.h"

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

template <class T=double>
Point<T> randIntPt(int lim) {
    return Point<T>(rand()%(lim*2) - lim, rand()%(lim*2)-lim);
}
