/**
 * Author:
 * Date: 2010-11-18
 * Source: tinyKACTL
 * Description:
 */
#pragma once

void queens(int N, int *cols) {
	int n = N & ~1, a1 = 1, a2 = 0;
	if (n % 6 == 2) a1 = n/2-1, a2 = n/2+2;
	rep(i,0,n/2) cols[i] = (a1+2*i)%n, cols[i+n/2] = (a2+2*i)%n;
	if (N & 1) cols[n] = n;
}
