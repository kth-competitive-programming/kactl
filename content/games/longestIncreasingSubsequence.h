/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-16
 * Source:
 * Description: Returns the length of the longest increasing subsequence of the elements in the range from begin to end.
 * Status: not tested
 * Usage:
 * Time: O(n\log n)
 */
#pragma once
#include "Point.h"

template <class It>
int lisLength(It begin, It end) {
	typedef typename iterator_traits<It>::value_type T;
	T inf = max_element(begin,end); //or 1<<30 or 1.0/0
	vector<T> best(end-begin,inf);
	for (It i = begin; i != end; ++i)
		*lower_bound(best.begin(),best.end(),*i) = *i;
	return lower_bound(best.begin(),best.end(),inf)-best.begin();
}
