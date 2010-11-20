/**
 * Author: Lukas Polacek
 * Date: 2009-10-27
 * Source: folklore
 * Description: Calculates determinant using modular
 * arithmetics. Can be rewritten to use doubles.
 * Status: tested
 * Time: $O(N^3)$
 */
#include "../number theory/modularArithmetic.h"

template<class Z> Mod<Z>
det(Mod<Z> a[100][100], int n) {
	Mod<Z> res(1);
	rep(k,0,n) {
		if (a[k][k].x == 0) rep(i,k+1,n) if (a[i][k].x != 0) {
			res = res * -Mod<Z>(1);
			rep(j,k,n) swap(a[k][j], a[i][j]);
			break;
		}
		if (a[k][k].x == 0) return Mod<Z>(0);
		Mod<Z> v = a[k][k];
		rep(i,k,n) a[k][i] = a[k][i] / v;
		res = res * v;
		rep(i,k+1,n) if (a[i][k].x != 0) {
			v = -a[i][k];
			rep(j,k,n) a[i][j] = a[i][j] + v * a[k][j];
		}
	}
	return res;
}
