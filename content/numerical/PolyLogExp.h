/**
 * Author: chilli, Andrew He, Adamant
 * Date: 2019-04-27
 * Description: A FFT based Polynomial class.
 */
#pragma once

#include "PolyBase.h"
#include "PolyInverse.h"
#include "PolyIntegDeriv.h"

poly log(poly a) {
	return modK(integr(deriv(a) * inverse(a)), sz(a));
}
poly exp(poly a) {
	poly b(1, num(1));
	if (a.empty())
		return b;
	while (sz(b) < sz(a)) {
		b.resize(sz(b) * 2);
		b *= (poly({num(1)}) + modK(a, sz(b)) - log(b));
		b.resize(sz(b) / 2 + 1);
	}
	return modK(b, sz(a));
}