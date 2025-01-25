/**
 * Author: Sachin Sivakumar
 * Date: 2025-01-23
 * Source: https://github.com/programming-team-code/programming_team_code/blob/main/monotonic_stack/count_rectangles.hpp
 * Description: Counts the number of rectangles of every size that fit in a grid where 1 represents a filled cell.
 * Time: O(NM)
 * Status: Tested on CSES Maximum Building II
 */
#pragma once

vvi count_rectangles(vvi &grid) {
	int n = sz(grid), m = sz(grid[0]);
	vvi ans(n+1, vi(m+1));
	vi col(m); // free space in column
	rep(r, 0, n) {
		rep(c, 0, m)
			if(grid[r][c]) col[c] = 0;
			else col[c]++;
		vi pre(m, -1), nex(m, m); // nearest < on left, <= on right
		rep(c, 0, m) {
			int i = c-1;
			while(i >= 0 && col[i] >= col[c]) {
				nex[i] = c;
				i = pre[i];
			}
			pre[c] = i;
		}
		rep(c, 0, m) {
			int left = c - pre[c] - 1, right = nex[c] - c - 1;
			ans[col[c]][left + right + 1]++;
			ans[col[c]][left]--;
			ans[col[c]][right]--;
		}
	}
	rep(i, 1, n+1)
		rep(t, 0, 2)
			for(int j = m-1; j; j--) ans[i][j] += ans[i][j+1];
	rep(j, 1, m+1)
		for(int i = n-1; i; i--) ans[i][j] += ans[i+1][j];
	return ans;
}
