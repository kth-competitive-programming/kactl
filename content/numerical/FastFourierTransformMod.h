/**
 * Author: chilli
 * Date: 2019-04-25
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Description: Higher precision FFT, can be used for convolutions modulo arbitrary integers.
 * Is safe in practice as long as $(|a|+|b|)\sqrt{\max(a)\max(b)} < \mathtt{\sim} 10^{15}$.
 * Time: O(N \log N), where $N = |A|+|B|-1$ (twice as slow as NTT or FFT)
 * Status: somewhat tested
 */
#pragma once

#include "FastFourierTransform.h"

template <int M> vi convMod(const vi &a, const vi &b) {
	if (a.empty() || b.empty()) return {};
	vi res(sz(a) + sz(b) - 1);
	int B = 32 - __builtin_clz(sz(res)), n = 1<<B, cut = sqrt(M);
	vector<C> L(n), R(n), outs(n), outl(n);
	rep(i,0,sz(a)) L[i] = C(a[i] / cut, a[i] % cut);
	rep(i,0,sz(b)) R[i] = C(b[i] / cut, b[i] % cut);
	fft(L, n, B), fft(R, n, B);
	rep(i,0,n) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl, n, B), fft(outs, n, B);
	rep(i,0,sz(res)) {
		ll av = ll(outl[i].real()+.5), cv = ll(outs[i].imag()+.5);
		ll bv = ll(outl[i].imag()+.5) + ll(outs[i].real()+.5);
		res[i] = int(((av % M * cut + bv % M) * cut + cv % M) % M);
	}
	return res;
}
