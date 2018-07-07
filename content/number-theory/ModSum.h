/**
 * Author: Simon Lindholm
 * Date: 2015-06-23
 * License: CC0
 * Source: own work
 * Description: Sums of mod'ed arithmetic progressions.
 *
 * \texttt{modsum(to, c, k, m)} = $\sum_{i=0}^{to-1}{(ki+c) \% m}$.
 * \texttt{divsum} is similar but for floored division.
 * Status: Tested for |k|,|c|,to,m <= 50, and on "aladin" on kattis.
 * Time: $\log(m)$, with a large constant.
 */
#pragma once

typedef unsigned long long ull;
ull sumsq(ull to) { return to / 2 * ((to-1) | 1); }

ull divsum(ull to, ull c, ull k, ull m) {
	ull res = k / m * sumsq(to) + c / m * to;
	k %= m; c %= m;
	if (k) {
		ull to2 = (to * k + c) / m;
		res += to * to2;
		res -= divsum(to2, m-1 - c, m, k) + to2;
	}
	return res;
}

ll modsum(ull to, ll c, ll k, ll m) {
	c = ((c % m) + m) % m;
	k = ((k % m) + m) % m;
	return to * c + k * sumsq(to) - m * divsum(to, c, k, m);
}
