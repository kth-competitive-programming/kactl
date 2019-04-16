/**
 * Author: Simon Lindholm
 * Date: 2016-09-10
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: Can be used for convolutions modulo specific nice primes
 * of the form $2^a b+1$, where the convolution result has size at most $2^a$.
 * For other primes/integers, use two different primes and combine with CRT.
 * May return negative values.
 * Time: O(N \log N)
 * Status: Somewhat tested
 */
#pragma once

#include "ModPow.h"

const ll mod = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

int mul(int a, int b) { return (ll)a * b % mod; }
int sub(int a, int b) { return b > a ? a - b + mod : a - b; }
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
void ntt(vi &a, vi &rt, vi &rev, int n) {
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k) {
                int z = mul(rt[j + k], a[i + j + k]);
                a[i + j + k] = sub(a[i + j], z);
                a[i + j] = add(a[i + j], z);
            }
}

vi conv(const vi &a, const vi &b) {
    if (a.empty() || b.empty())
        return {};
    vi res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vi inl(n), inr(n);
    vi out(n), rt(n, 1);
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    int curL = (mod - 1) >> 2;
    for (int k = 2; k < n; k *= 2) {
        int z[] = {1, modpow(root, curL)};
        curL >>= 1;
        rep(i, k, 2 * k) rt[i] = mul(rt[i / 2], z[i & 1]);
    }
    copy(all(a), begin(inl)), copy(all(b), begin(inr));
    ntt(inl, rt, rev, n), ntt(inr, rt, rev, n);
    int invN = modpow(n, mod - 2);
    rep(i, 0, n) out[i] = mul(mul(inl[i], inr[i]), invN);
    reverse(out.begin() + 1, out.begin() + n);
    ntt(out, rt, rev, n);
    rep(i, 0, sz(res)) res[i] = out[i];
    return out;
}
