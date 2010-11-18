/**
 * Author: Håkan Terelius
 * Date: 2010-11-07
 * Source: Wikipedia
 * Description: Finds the longest common substring. A linear solution is possible with suffix trees.
 * Status: Untested!
 * Time: $O(nm)$ where n and m are the lengths of the sequences.
 * Memory: $O(m)$, swap to get $O(\min(n,m))$
 */
#pragma once

#include <vector>
#include <algorithm>
using namespace std;

template <class T> size_t lcsubstring(const T &X, const T &Y) {
	const int l1 = X.size(), l2 = Y.size();
	if(!l1 || !l2) return 0;
	vector<int> d1(l2), d2(l2);
	int l = 0;
	rep(i,0,l1) {
		rep(j,0,l2)
			l = max(l, d1[j]=X[i]!=Y[j]?0:(!i||!j?1:1+d2[j-1]));
			// The substrings ends with the maximizing indicies i,j
		d1.swap(d2);
	}
	return l;
}