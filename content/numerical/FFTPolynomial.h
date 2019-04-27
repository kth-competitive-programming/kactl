/**
 * Author: chilli
 * Date: 2019-04-27
 * Description: A FFT based Polynomial class.
 */
#pragma once

#include "../number-theory/ModularArithmetic.h"
#include "FastFourierTransform.h"
#include "FastFourierTransformMod.h"

typedef Mod num;
typedef vector<num> poly;
vector<Mod> conv(vector<Mod> a, vector<Mod> b) {
    auto res = convMod<mod>(vl(all(a)), vl(all(b)));
    return vector<Mod>(all(res));
}
poly &operator+=(poly &a, poly &b) {
    a.resize(max(sz(a), sz(b)));
    rep(i,0,sz(b)) a[i] = a[i] + b[i];
    return a;
}
poly &operator-=(poly &a, poly b) {
    a.resize(max(sz(a), sz(b)));
    rep(i,0,sz(b)) a[i] = a[i] - b[i];
    return a;
}
poly &operator*=(poly &a, poly &b) { return a = conv(a, b); }
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
        B = modK(B * (poly({num(2)}) - A * B), 2 * sz(B));
    return modK(B, sz(A));
}
poly &operator/=(poly &a, poly &b) {
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
poly deriv(poly a) {
    if (a.empty())
        return {};
    poly b(sz(a) - 1);
    rep(i, 1, sz(a)) b[i - 1] = a[i] * num(i);
    return b;
}
poly integr(poly a) {
    if (a.empty())
        return {};
    poly b(sz(a) + 1);
    rep(i, 0, sz(a) + 1) b[i + 1] = a[i] / num(i + 1);
    return b;
}
