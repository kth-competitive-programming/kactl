#pragma once

#include "PolynomialMod.h"

vector<num> eval(const poly &a, const vector<num> &x) {
	int n = sz(x);
	if (!n) return {};
	vector<poly> up(2 * n);
	rep(i, 0, n) up[i + n] = poly({num(0) - x[i], 1});
	for (int i = n - 1; i > 0; i--)
		up[i] = up[2 * i] * up[2 * i + 1];
	vector<poly> down(2 * n);
	down[1] = a % up[1];
	rep(i, 2, 2 * n) down[i] = down[i / 2] % up[i];
	vector<num> y(n);
	rep(i, 0, n) y[i] = down[i + n][0];
	return y;
}
