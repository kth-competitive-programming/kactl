/**
 * Author: Simon Lindholm
 * Date: 2015-05-12
 * Source: own work
 * Description:
 * Find the smallest i in $[a,b]$ that maximizes $f(i)$, assuming that $f(a) < \dots < f(i) \ge \dots \ge f(b)$.
 * To reverse which of the sides allows non-strict inequalities, change the < marked with (A) to <=, and reverse the loop at (B).
 * To minimize $f$, change it to >, also at (B).
 *
 * For greater performance, replace the first part by a golden section search with
 * parameters $a, b, x \mapsto f(\lfloor x \rfloor), \epsilon = 5$, and \texttt{long double} if $b > 2^{52}$.
 * Status: tested
 * Usage:
	int ind = ternSearch(0,n,[\&](int i){return a[i];});
 * Time: O(\log\left(\frac{b-a}{\epsilon}\right))
 */
#pragma once

template<class F>
int ternSearch(int a, int b, F f) {
	assert(a <= b);
	while (b - a >= 3) {
		int d = (b - a) / 3, lo = a + d, hi = b - d;
		if (f(lo) < f(hi)) // (A)
			a = lo;
		else
			b = hi;
	}
	int r = a;
	rep(i,a+1,b+1) if (f(r) < f(i)) r = i; // (B)
	return r;
}
