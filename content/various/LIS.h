/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Compute indices for the longest increasing subsequence.
 * Status: Tested on Kattis, longincsubseq
 * Time: $O(N \log N)$
 */
#pragma once

template<class I> vi lis(vector<I> S) {
	vi prev(sz(S));
	typedef pair<I, int> p;
	vector<p> res;
	rep(i,0,sz(S)) {
		p el { S[i], i };
		//S[i]+1 for non-decreasing
		auto it = lower_bound(all(res), p { S[i], 0 }); 
		if (it == res.end()) res.push_back(el), it = --res.end();
		*it = el;
		prev[i] = it==res.begin() ?0:(it-1)->second; 
	}
	int L = sz(res), cur = res.back().second;
	vi ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
	return ans;
}
