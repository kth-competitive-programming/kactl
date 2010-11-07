/**
 * Author: Håkan Terelius
 * Date: 2010-11-07
 * Source: tinyKACTL, newKACTL, Wikipedia
 * Description: Compute indices for the longest increasing subsequence in specified input sequence.
 * Time: $O(n\log n)$ where n is the length of input sequence.
 */
#pragma once

template<class It> struct It_Less {
	bool operator()(It i, It j) const {return *i < *j;} };

template<class It> vector<size_t> lis3(It begin, It end) {
	if(begin == end) return vector<size_t>();
	vector<It> idx, back(end-begin);
	idx.push_back(end);
	for(It it = begin; it != end; ++it) {
		// upper_bound if non-decreasing rather than increasing
		typeof(idx.begin()) b = lower_bound(idx.begin() + 1, idx.end(), it, It_Less<It>());
		back[it-begin] = *(b-1);
		if(b == idx.end()) idx.push_back(it); else *b = it;
	}
	size_t len = idx.size()-1, last = idx.back()-begin;
	vector<size_t> ind(len);
	while(len) ind[--len] = last, last = back[last]-begin;
	return ind;
}
