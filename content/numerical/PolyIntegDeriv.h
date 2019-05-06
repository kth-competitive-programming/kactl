/**
 * Author: chilli, Andrew He, Adamant
 * Date: 2019-04-27
 * Description: A FFT based Polynomial class.
 */
#pragma once
#include "PolyBase.h"

poly deriv(poly a) {
	if (a.empty()) return {};
	poly b(sz(a) - 1);
	rep(i, 1, sz(a)) b[i - 1] = a[i] * num(i);
	return b;
}
poly integr(poly a) {
	if (a.empty()) return {0};
	poly b(sz(a) + 1);
	b[1] = num(1);
	rep(i, 2, sz(b)) b[i] = b[mod%i]*Mod(-mod/i+mod);
	rep(i, 1 ,sz(b)) b[i] = a[i-1] * b[i];
	return b;
}
