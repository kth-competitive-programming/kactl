/**
 * Author: chilli, Andrew He, Adamant
 * Date: 2019-04-27
 * Description: A FFT based Polynomial class.
 */
#pragma once

#include "PolyBase.h"
#include "PolyLogExp.h"

poly pow(poly a, ll m) {
	int p = 0, n = sz(a);
	while (p < sz(a) && a[p].x == 0)
		++p;
	if (ll(m)*p >= sz(a)) return poly(sz(a));
	num j = a[p];
	a = {a.begin() + p, a.end()};
	a = a * (num(1) / j);
	a.resize(n);
	auto res =  exp(log(a) * num(m)) * (j ^ m);
	res.insert(res.begin(), p*m, 0);
	return {res.begin(), res.begin()+n};
}
