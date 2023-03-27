/**
 * Author: Johan Sannemo
 * Date: 2014-11-28
 * License: CC0
 * Source: Folklore
 * ExtDesc: Calculate submatrix sums quickly, given upper-left and lower-right corners (half-open). O(N^2 + Q)
 * Status: Tested on Kattis
 */
#pragma once

template<class T>
struct SubMatrix {
	vector<vector<T>> p;
	SubMatrix(vector<vector<T>>& v) {
		int R = sz(v), C = sz(v[0]);
		p.assign(R+1, vector<T>(C+1));
		rep(r,0,R) rep(c,0,C)
			p[r+1][c+1] = v[r][c] + p[r][c+1] + p[r+1][c] - p[r][c];
	}
	T sum(int u, int l, int d, int r) {
		return p[d][r] - p[d][l] - p[u][r] + p[u][l];
	}
};
