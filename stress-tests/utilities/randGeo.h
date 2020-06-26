#pragma once

#include "../../content/geometry/Point.h"

template <class T=double>
Point<T> randIntPt(int lim) {
    return Point<T>(rand()%(lim*2) - lim, rand()%(lim*2)-lim);
}
