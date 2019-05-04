#pragma once

#include "PolynomialBase.h"
poly deriv(poly a) {
	if (a.empty())
		return {};
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
	return modK(res, n);
}
