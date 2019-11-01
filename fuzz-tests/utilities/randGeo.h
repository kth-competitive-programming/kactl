#pragma once

#include <bits/stdc++.h>
#include "../../content/geometry/Point.h"

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

Point<double> randPt(int lim) {
    return Point<double>(rand()%(lim*2) - lim, rand()%(lim*2)-lim);
}
