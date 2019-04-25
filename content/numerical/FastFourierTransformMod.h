/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Papers about accuracy: http://www.daemonology.net/papers/fft.pdf, http://www.cs.berkeley.edu/~fateman/papers/fftvsothers.pdf
   For integers rounding works if $(|a| + |b|)\max(a, b) < \mathtt{\sim} 10^9$, or in theory maybe $10^6$.
 * Description: fft(a, ...) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divide by n, reverse(start+1, end), FFT back.
   For integers, consider using a number-theoretic transform instead, to avoid rounding issues.
 * Time: O(N \log N), where $N = |A|+|B|-1$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 */
#pragma once

#include "FastFourierTransform.h"

template <int M>
vi convMod(const vi &a, const vi &b) {
	if (a.empty() || b.empty()) return {};
	vi res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L, cut = sqrt(M);
	vector<C> inl(n), inr(n), outs(n), outl(n);
	rep(i, 0, a.size()) inl[i] = {a[i] / cut, a[i] % cut};
	rep(i, 0, b.size()) inr[i] = {b[i] / cut, b[i] % cut};
	fft(inl, n, L), fft(inr, n, L);
	rep(i, 0, n) {
		int j = -i & (n - 1);
		outl[j] = (inl[i] + conj(inl[j])) * inr[i] / (2.0 * n);
		outs[j] = (inl[i] - conj(inl[j])) * inr[i] / (2.0 * n) / 1i;
	}
	fft(outl, n, L), fft(outs, n, L);
	rep(i, 0, sz(res)) {
		ll av = round(outl[i].real()), cv = round(outs[i].imag());
		ll bv = round(outl[i].imag()) + round(outs[i].real());
		res[i] = vi(((av % M * cut + bv % M) * cut + cv % M) % M);
	}
	return res;
}
