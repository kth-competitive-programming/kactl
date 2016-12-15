/**
 * Author: Håkan Terelius
 * Date: 2010-11-07
 * Source: Wikipedia
 * Description: Finds the longest common subsequence.
 * Time: $O(nm)$ where n and m are the lengths of the sequences.
 * Memory: $O(nm)$.
 */
#pragma once

#include <algorithm>
using namespace std;

template <class T> T lcs(const T &X, const T &Y) {
	const int l1 = X.size(), l2 = Y.size();
	vector<vi> dp(l1+1, vi(l2+1));
	rep(i,0,l1+1) dp[i][0] = 0;
	rep(i,0,l2+1) dp[0][i] = 0;
	rep(i,1,l1+1)
		rep(j,1,l2+1)
			dp[i][j] = X[i-1]==Y[j-1] ? dp[i-1][j-1]+1 :
				max(dp[i][j-1],dp[i-1][j]);
	int len = dp[l1][l2], i=l1, j=l2;
	T ans(len,0);
	while(i && j)
		if(X[i-1]==Y[j-1]) ans[--len] = X[--i], --j;
		else if(dp[i][j-1]>dp[i-1][j]) --j;
		else --i;
	return ans;
}
