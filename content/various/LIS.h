/**
 * Author: Håkan Terelius
 * Date: 2010-11-07
 * Source: tinyKACTL, newKACTL, Wikipedia
 * Description: Compute indices for the longest increasing subsequence in specified input sequence.
 * Time: $O(n\log n)$ where n is the length of input sequence.
 */
#pragma once

#include <vector>
using namespace std;

template<class I> vi lis3(I begin, I end) {
	struct {bool operator()(I i, I j) const {return *i<*j;}} cmp;
	if(begin == end) return {};
	vector<I> idx, back(end-begin);
	idx.push_back(end);
	for(I it = begin; it != end; ++it) {
		// upper_bound if non-decreasing rather than increasing
		auto b = lower_bound(idx.begin() + 1, idx.end(), it, cmp);
		back[it-begin] = *(b-1);
		if(b == idx.end()) idx.push_back(it); else *b = it;
	}
	int len = idx.size()-1, last = idx.back()-begin;
	vi ind(len);
	while(len) ind[--len] = last, last = back[last]-begin;
	return ind;
}
