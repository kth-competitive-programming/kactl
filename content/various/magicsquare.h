/**
* Author:
* Date: 2010-11-18
* Source: tinyKACTL
* Description:
*/
#pragma once

#include <algorithm>
using namespace std;

int sol[500][500];

void magic_odd(int n, int y0, int x0, int add) {
	int x = n/2, y = 0;
	for(int i=0; i<n*n; ++i, ++x, --y) {
		if (x == n) x = 0;
		if (y < 0) y = n-1;
		if (sol[y0+y][x0+x] !=-1) {
			if (--x < 0) x = n-1;
			if ((y += 2) >= n) y-= n;
		}
		sol[y0+y][x0+x] = i+add;
	}
}
void magic_4mul(int n, int add) {
	for (int r = 0, base = 0; r < n/2; ++r, base += n) {
		rep(i,0,n) {
			bool b = (((i+1)/2) & 1) ^ (r & 1);
			sol[r][i] = ((b ? n*n-i-base-1 : i+base)) + add;
			sol[n-r-1][n-i-1] = n*n-sol[r][i]-1 + 2*add;
		}
	}
}

bool magic_square(int n, int sum) {
	if (n == 2 || (sum - n*(n*n-1)/2) % n) return false;
	int add = (sum-n*(n*n-1)/2)/n;
	memset(sol, -1, sizeof(sol));
	if (n & 1) magic_odd(n, 0, 0, add);
	else if (!(n & 3)) magic_4mul(n, add);
	else {
		magic_odd(n/2, 0, 0, add);
		magic_odd(n/2, n/2, 0, add + 3*n*n/4);
		magic_odd(n/2, 0, n/2, add + n*n/2);
		magic_odd(n/2, n/2, n/2, add + n*n/4);
		rep(i, 0, n/2) rep(j,0,n/4)
			swap(sol[i][j+(i==n/4)], sol[i+n/2][j+(i==n/4)]);
		rep(i,n-n/4+1,n) rep(j,0,n/2)
			swap(sol[j][i], sol[j+n/2][i]);
	}
	return true;
}
