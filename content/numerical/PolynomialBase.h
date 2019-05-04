/**
 * Author: chilli, Andrew He, Adamant
 * Date: 2019-04-27
 * Description: A FFT based Polynomial class.
 */
#pragma once

#include "../number-theory/ModularArithmetic.h"
#include "FastFourierTransform.h"
#include "FastFourierTransformMod.h"
// #include "NumberTheoreticTransform.h"

typedef Mod num;
typedef vector<num> poly;
vector<Mod> conv(vector<Mod> a, vector<Mod> b) {
	auto res = convMod<mod>(vl(all(a)), vl(all(b)));
	// auto res = conv(vl(all(a)), vl(all(b)));
	return vector<Mod>(all(res));
}
poly &operator+=(poly &a, const poly &b) {
	a.resize(max(sz(a), sz(b)));
	rep(i, 0, sz(b)) a[i] = a[i] + b[i];
	return a;
}
poly &operator-=(poly &a, const poly &b) {
	a.resize(max(sz(a), sz(b)));
	rep(i, 0, sz(b)) a[i] = a[i] - b[i];
	return a;
}

poly &operator*=(poly &a, const poly &b) {
	if (sz(a) + sz(b) < 100){
		poly res(sz(a) + sz(b) - 1);
		rep(i,0,sz(a)) rep(j,0,sz(b))
			res[i + j] = (res[i + j] + a[i] * b[j]);
		return (a = res);
	}
	return a = conv(a, b);
}
poly operator*(poly a, const num b) {
	poly c = a;
	trav(i, c) i = i * b;
	return c;
}
#define OP(o, oe) \
	poly operator o(poly a, poly b) { \
		poly c = a; \
		return c oe b; \
	}
OP(*, *=) OP(+, +=) OP(-, -=);
poly modK(poly a, int k) { return {a.begin(), a.begin() + min(k, sz(a))}; }
poly inverse(poly A) {
	poly B = poly({num(1) / A[0]});
	while (sz(B) < sz(A))
		B = modK(B * (poly({num(2)}) - modK(A, 2*sz(B)) * B), 2 * sz(B));
	return modK(B, sz(A));
}