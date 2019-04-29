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
poly &operator*=(poly &a, const poly &b) { return a = conv(a, b); }
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
// Currently there's two of them - the second is the original one (simply following the formula), the first one is a version Adamant says is faster.
// I haven't been able to replicate the difference in performance, however.
poly inverse(poly A) {
    poly B = poly({num(1) / A[0]});
    while (sz(B) < sz(A)){
        poly C = B*modK(A, 2*sz(B));
        C = poly(C.begin()+sz(B), C.end());
        C = modK(B*C, sz(B));
        C.insert(C.begin(), sz(B), 0);
        B -= C;
    }
    return modK(B, sz(A));
}
// poly inverse(poly A) {
//     poly B = poly({num(1) / A[0]});
//     while (sz(B) < sz(A))
//         B = modK(B * (poly({num(2)}) - modK(A, 2*sz(B)) * B), 2 * sz(B));
//     return modK(B, sz(A));
// }
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
poly log(poly a) { return modK(integr(deriv(a) * inverse(a)), sz(a)); }
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
    int p = 0; int n = sz(a);
    while (p < sz(a) && a[p].x == 0)
        ++p;
    num j = a[p];
    a = {a.begin() + p, a.end()};
    a = a * (num(1) / j);
    a.resize(n);
    auto res =  exp(log(a) * num(m)) * (j ^ m);
    res.insert(res.begin(), p*m, 0);
    return modK(res, n);
}

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

poly interp(vector<num> x, vector<num> y) {
    int n = sz(x);
    vector<poly> up(n * 2);
    rep(i, 0, n) up[i + n] = poly({num(0) - x[i], num(1)});
    for (int i = n - 1; i > 0; i--)
        up[i] = up[2 * i] * up[2 * i + 1];
    vector<num> a = eval(deriv(up[1]), x);
    vector<poly> down(2 * n);
    rep(i, 0, n) down[i + n] = poly({y[i] * (num(1) / a[i])});
    for (int i = n - 1; i > 0; i--)
        down[i] = down[i * 2] * up[i * 2 + 1] + down[i * 2 + 1] * up[i * 2];
    return down[1];
}