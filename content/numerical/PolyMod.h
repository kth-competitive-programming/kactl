/**
 * Author: chilli, Andrew He, Adamant
 * Date: 2019-04-27
 * Description: A FFT based Polynomial class.
 */
#pragma once

#include "PolyBase.h"

poly &operator/=(poly &a, poly b) {
	if (sz(a) < sz(b))
		return a = {};
	int s = sz(a) - sz(b) + 1;
	reverse(all(a)), reverse(all(b));
	a.resize(s), b.resize(s);
	a = a * inverse(b);
	a.resize(s), reverse(all(a));
	return a;
}
OP(/, /=)
poly &operator%=(poly &a, poly &b) {
	if (sz(a) < sz(b))
		return a;
	poly c = (a / b) * b;
	a.resize(sz(b) - 1);
	rep(i, 0, sz(a)) a[i] = a[i] - c[i];
	return a;
}
OP(%, %=)