/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-12
 * Source: Common sense
 * Description: Given a set of intervals given as pairs of start and end this function returns a set of intervals with the same coverage but with overlapping and touching intervals merged. Input is given as iterators with value type pair<T,T> whos range will be sorted. The result is returned as a sorted vector of the resulting intervals.
 * Status: not tested
 * Usage:
 vector<pair<int,int> > v;
 v = intervalUnion<int>(v.begin(), v.end());
 * Time: O(n\log n)
 * Problems: UVa 11355 - Cool Points
 */
#pragma once

template <class T, class It>
vector<pair<T,T> > intervalUnion(It begin, It end) {
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
