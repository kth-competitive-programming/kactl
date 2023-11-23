/**
 * Author:
 * Description: 
 * Usage: 
 * Time: 
 */
#pragma once

// Caution! prim needs to be initialized with prim = power(primitive root of MOD, A) before use;
// multiply: input format - [x^0 coeff, x^1 coeff, ...], [same], [anything]
const int MOD = 998244353;
const int A = 119, B = 23;
ll prim;
ll power(ll a, int pow) {
    ll ret = 1;
    while (pow > 0) {
        if (pow & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        pow /= 2;
    }
    return ret;
}
void fft(vector<ll>& a, bool inv) {
    int n = a.size();
    for (int dest=1, src=0; dest<n; ++dest) {
        int bit = n / 2;
        while (src >= bit) {
            src -= bit;
            bit /= 2;
        }
        src += bit;
        if (dest < src) { swap(a[dest], a[src]); }
    }
    for (int len=2; len <= n; len *= 2) {
        ll unity = power(inv ? power(prim, MOD-2) : prim, (1 << B) / len);
        for (int i=0; i<n; i+=len) {
            ll w = 1;
            for (int j=0; j<len/2; ++j) {
                ll u = a[i+j], v = a[i+j+len/2] * w % MOD;
                a[i+j] = u+v;
                if (a[i+j] >= MOD) a[i+j] -= MOD;
                a[i+j+len/2] = u-v;
                if (a[i+j+len/2] < 0) a[i+j+len/2] += MOD;
                w = w * unity % MOD;
            }
        }
    }
    if (inv) {
        ll tmp = power(n, MOD-2);
        for (int i=0; i<n; ++i) a[i] = a[i] * tmp % MOD;
    }
}
void conv(const vector<ll>& a, const vector<ll>& b, vector<ll>& result) {
    result.resize(a.size(), 0);
    for (int i=0; i<result.size(); ++i) result[i] = (result[i] + a[i] * b[i]) % MOD;
}