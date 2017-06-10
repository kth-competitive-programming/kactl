/**
 * Author: Lukas Polacek
 * Date: 2009-11-01
 * License: CC0
 * Source: tinyKACTL, http://en.wikipedia.org/wiki/Binomial_coefficient
 * Description: The number of $k$-element subsets of an $n$-element set, $\binom{n}{k}=\frac{n!}{k!(n-k)!}$
 * Time: O(\min(k,n-k))
 */
#pragma once

ll choose(int n, int k) {
	ll c = 1, to = min(k, n-k);
	if (to < 0) return 0;
	rep(i,0,to) c = c * (n - i) / (i + 1);
	return c;
}
