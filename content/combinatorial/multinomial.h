/**
 * Author:
 * Date: 2009-09-25
 * Source: tinyKACTL
 * Description: $\binom{\sum k_i}{k_1,k_2,...,k_n}=\frac{(\sum k_i)!}{k_1!k_2!...k_n!}$
 * Time: O((\sum k_i)-k_1)
 */
#pragma once
#include <algorithm>
using namespace std;

template<class T, class V>
T multinomial(int n, V &k) {
	T c = 1;
	int m=k[0];
	for(int i=1;i<n;++i)
		for(int j=1;j<=k[i];++j)
			c*=++m, c/=j;
	return c;
}
