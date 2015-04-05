/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-12
 * Source: Common sense
 * Description: Given a set of intervals given as pairs of start and end this function returns a set of intervals with the same coverage but with overlapping and touching intervals merged. Input is given as iterators with value type pair<T,T> whos range will be sorted. The result is returned as a sorted vector of the resulting intervals.
 * Status: not tested, to be tested with UVa 11355 - Cool Points
 * Usage:
 vpii v = intervalUnion<int>(all(v));
 * Time: O(n\log n)
 */
#pragma once

#include <vector>
using namespace std;

template <class T, class It>
vector<pair<T,T> > intervalUnion(It begin, It end) {
	if (end==begin) return {};
	sort(begin, end);
	vector<pair<T,T> > res(1, *begin);
	for (It i = ++begin; i != end; ++i) {
		if (res.back().second < i->first)
			res.push_back(*i);
		else if (res.back().second < i->second)
			res.back().second = i->second;
	}
	return res;
}
