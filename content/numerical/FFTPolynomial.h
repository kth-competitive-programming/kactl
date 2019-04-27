/**
 * Author: chilli
 * Date: 2019-04-27
 * Description: A FFT based Polynomial class.
 */
#pragma once

#include "FastFourierTransform.h"

typedef double num;
typedef vector<num> poly;
poly &operator+=(poly &a, poly &b) {
    a.resize(max(sz(a), sz(b)));
    rep(i, 0, sz(b)) a[i] += b[i];
    return a;
}
poly &operator-=(poly &a, poly b) {
    a.resize(max(sz(a), sz(b)));
    rep(i, 0, sz(b)) a[i] -= b[i];
    return a;
}
poly &operator*=(poly &a, poly &b) { return a = conv(a, b); }
#define OP(o, oe) \
    poly operator o(poly a, poly b) { \
        poly c = a; \
        return c oe b; \
    }
OP(*, *=) OP(+, +=) OP(-, -=);
