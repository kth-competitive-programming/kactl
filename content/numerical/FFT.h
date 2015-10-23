/**
 * Author: Simon Lindholm
 * Date: 2015-06-25
 * Source: http://rosettacode.org/wiki/Fast_Fourier_transform
 * Description: In-place fast Fourier transform. Also includes a function for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$. $a$ and $b$ should be of roughly equal size.
   See also Karatsuba, under the Various chapter.
 * Time: O(N \log N)
 * Status: somewhat tested
 */
#pragma once
#include <valarray>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

typedef valarray<complex<double> > carray;
const double PI = acos(-1);
void fft(carray& x) {
	int N = sz(x);
	if (N <= 1) return;
	carray even = x[slice(0, N/2, 2)];
	carray odd = x[slice(1, N/2, 2)];
	fft(even);
	fft(odd);
	rep(k,0,N/2) {
		auto t = polar(1.0, -2 * M_PI * k / N) * odd[k];
		x[k    ] = even[k] + t;
		x[k+N/2] = even[k] - t;
	}
}

void ifft(carray& x) {
	fft(x = x.apply(conj));
	x = x.apply(conj) / sz(x);
}

typedef vector<double> vd;
vd conv(const vd& a, const vd& b) {
	int s = sz(a) + sz(b) - 1, L = 32 - __builtin_clz(s);
	if (s <= 0) return {};
	carray av(1 << L), bv = av;
	copy(all(a), begin(av)); fft(av);
	copy(all(b), begin(bv)); fft(bv);
	carray cv = av * bv; ifft(cv);
	vd c(s); rep(i,0,s) c[i] = cv[i].real();
	return c;
}
