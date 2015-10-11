/**
 * Author: Edits by Simon Lindholm
 * Date: 2015-10-11
 * Source: tinyKACTL
 * Description: $\binom{\sum k_i}{k_1,k_2,...,k_n}=\frac{(\sum k_i)!}{k_1!k_2!...k_n!}$
 * Time: O((\sum k_i)-k_1)
 * Status: Tested on kattis:lexicography
 */
#pragma once
#include <algorithm>
using namespace std;

ll multinomial(vi& v) {
	ll c = 1;
	int m = v.empty() ? 1 : v[0];
	rep(i,1,sz(v)) rep(j,0,v[i])
		c = c * ll(++m) / (j+1);
	return c;
}
