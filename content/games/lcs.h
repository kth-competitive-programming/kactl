/**
 * Author: Håkan Terelius
 * Date: 2010-11-07
 * Source: Wikipedia
 * Description: Finds the longest common subsequence. DB solution based on the LCS function\\ $LCS(X_i,Y_j) = \left\{\begin{array}{ll}\O & i=0 \text{ or } j=0\\ \{LCS(X_{i-1},Y_{j-1}),x_i\} & x_i = y_j\\ \max(LCS(X_i,Y_{j-1}),LCS(X_{i-1},Y_j)) & x_i \neq y_j\end{array}\right.$
 * Time: $O(nm)$ where n and m are the lengths of the sequences.
 * Memory: $O(nm)$, can be reduced to $O(2*\min(n,m))$ for only length.
 */
#pragma once

const int MAXLEN = 1000;
int dp[MAXLEN][MAXLEN];

template <class T> T lcs(const T &X, const T &Y) {
	const int l1 = X.size(), l2 = Y.size();
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
		else --i; // Multiple solutions if dp[i][j-1]==dp[i-1][j]
	return ans;
}