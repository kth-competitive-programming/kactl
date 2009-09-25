/**
 * Author:
 * Date: 2009-08-08
 * Source: tinyKACTL, http://en.wikipedia.org/wiki/Binomial_coefficient
 * Description: $\binom{n}{k}=\frac{n!}{k!(n-k)!}$
 * Time: O(\min(k,n-k))
 */
#pragma once
#include <algorithm>
using namespace std;

template<class T>
T choose(int n, int k) {
	if(k>n || k<0) return 0;
	k = max(k, n-k);
	T c = 1;
	for(int i = 1; i <= n-k; ++i)
		c *= k+i, c /= i;
	return c;
}
