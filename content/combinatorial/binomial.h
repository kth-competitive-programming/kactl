/**
 * Author:
 * Date: 2009-08-08
 * Source: tinyKACTL, http://en.wikipedia.org/wiki/Binomial_coefficient
 * Description: The number of $k$-element subsets of an $n$-element set, $\binom{n}{k}=\frac{n!}{k!(n-k)!}$
 * Time: O(\min(k,n-k))
 */
#pragma once
#include <algorithm>
using namespace std;

template<class T>
T choose(int n, int k) {
	if(k>n || k<0) return T(0);
	k = min(k, n-k);
	T c(1);
	for(int i = 1; i <= k; ++i)
		c = c * T(n - i + 1) / T(i);
	return c;
}
