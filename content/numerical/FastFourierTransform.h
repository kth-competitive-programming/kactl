/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a, ...) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divide by n, reverse(start+1, end), FFT back.
   Let N be $\max(|a|,|b|)$. Is guaranteed safe as long as $N\log_2{N}\max(a)\max(b) < \mathtt{\sim} 10^{16}$ .
   Consider using number-theoretic transform or FFTMod instead if precision is an issue.
 * Time: O(N \log N), where $N = |A|+|B|-1$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 */
#pragma once

typedef complex<double> C;
typedef complex<long double> Cd;
typedef vector<double> vd;
void fft(vector<C> &a, int n, int L, vector<C> &rt) {
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	if (rt.empty()) {
		rt.assign(n, 1);
		for (int k = 2; k < n; k *= 2) {
			Cd z[] = {1, polar(1.0, M_PI / k)};
			rep(i, k, 2 * k) rt[i] = Cd(rt[i / 2]) * z[i & 1];
		}
	}
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)         /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+ k];              /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);                  /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd &a, const vd &b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n), rt;
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in, n, L, rt);
	trav(x, in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out, n, L, rt);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}
