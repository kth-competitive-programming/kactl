/**
 * Author: Simon Lindholm
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: http://rosettacode.org/wiki/Fast_Fourier_transform
   Papers about accuracy: http://www.daemonology.net/papers/fft.pdf, http://www.cs.berkeley.edu/~fateman/papers/fftvsothers.pdf
 * Description: Fast Fourier transform. Also includes a function for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$. $a$ and $b$ should be of roughly equal size.
   For convolutions of integers, rounding the results of conv
   works if $(|a| + |b|)\max(a, b) < \mathtt{\sim} 10^9$ (in theory maybe $10^6$);
   you may want to use an NTT from the Number Theory chapter instead.
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
void fft(carray& x, carray& roots) {
	int N = sz(x);
	if (N <= 1) return;
	carray even = x[slice(0, N/2, 2)];
	carray odd = x[slice(1, N/2, 2)];
	carray rs = roots[slice(0, N/2, 2)];
	fft(even, rs);
	fft(odd, rs);
	rep(k,0,N/2) {
		auto t = roots[k] * odd[k];
		x[k    ] = even[k] + t;
		x[k+N/2] = even[k] - t;
	}
}

typedef vector<double> vd;
vd conv(const vd& a, const vd& b) {
	int s = sz(a) + sz(b) - 1, L = 32-__builtin_clz(s), n = 1<<L;
	if (s <= 0) return {};
	carray av(n), bv(n), roots(n);
	rep(i,0,n) roots[i] = polar(1.0, -2 * M_PI * i / n);
	copy(all(a), begin(av)); fft(av, roots);
	copy(all(b), begin(bv)); fft(bv, roots);
	roots = roots.apply(conj);
	carray cv = av * bv; fft(cv, roots);
	vd c(s); rep(i,0,s) c[i] = cv[i].real() / n;
	return c;
}
