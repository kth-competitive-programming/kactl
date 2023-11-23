/**
 * Author:
 * Description: 
 * Usage: 
 * Time: 
 */
#pragma once

// multiply: input format - [x^0 coeff, x^1 coeff, ...], [same], [anything]
typedef complex<double> base;

const double PI = acos(-1);
void fft(vector<base>& a, bool inv) {
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
        double ang = 2 * PI / len * (inv ? -1 : 1);
        base unity(cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            base w(1, 0);
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= unity;
            }
        }
    }
    if (inv) {
        for (int i=0; i<n; ++i) { a[i] /= n; }
    }
}

void multiply(const vector<int>& a, const vector<int>& b, vector<int>& result) {
    int n = 2;
    while (n < a.size() + b.size()) { n *= 2; }

    vector<base> p(a.begin(), a.end());
    p.resize(n);
    for (int i=0; i<b.size(); ++i) { p[i] += base(0, b[i]); }
    fft(p, false);

    result.resize(n);
    for (int i=0; i<=n/2; ++i) {
        base u = p[i], v = p[(n-i) % n];
        p[i] = (u * u - conj(v) * conj(v)) * base(0, -0.25);
        p[(n-i) % n] = (v * v - conj(u) * conj(u)) * base(0, -0.25);
    }
    fft(p, true);
    for (int i=0; i<n; ++i) { result[i] = (int)round(p[i].real()); }
}

