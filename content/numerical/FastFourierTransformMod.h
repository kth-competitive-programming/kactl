/**
 * Author: chilli
 * Date: 2019-04-25
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Description: Can be used for convolutions modulo arbitrary integers.
 * Is essentially a higher precision FFT.
 * Is safe in practice as long as $(|a|+|b|)\sqrt{\max(a,b)} < \mathtt{\sim} 10^{15}$.
 * Time: O(N \log N), where $N = |A|+|B|-1$ (twice as slow as NTT or FFT)
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
