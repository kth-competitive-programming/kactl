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
P proj(P a, P b, P p, bool refl=false) {
	return p - (b-a).perp().unit()*(1+refl)*lineDist(a, b, p);
}
