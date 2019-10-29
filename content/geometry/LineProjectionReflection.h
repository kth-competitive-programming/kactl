/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-10-29
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Projects point p onto line ab. Set refl=true to reflect point p
 * across line ab. The algorithm uses products in intermediate steps so watch
 * out for overflow.
 * Status:
 */
#pragma once

#include "Point.h"
#include "lineDistance.h"

template <class P>
P lineProj(P a, P b, P p, bool refl=false) {
	P v = b - a;
	return p - v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}
