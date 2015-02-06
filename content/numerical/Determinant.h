/**
 * Author: Lukas Polacek
 * Date: 2009-10-27
 * Source: folklore
 * Description: Calculates determinant using modular arithmetics.
 * Can be rewritten to use doubles, but then use some epsilon to avoid division
 * by zero. The modulus is assumed to be a prime number. For composite moduli,
 * use CRT; for prime powers, you are screwed, but at least A is invertible iff
 * it is invertible mod p, and the identity $\det A = (\Pi^n_{k=1}(A^{-1}_k)_{k,k})^{-1}$
 * could be used on a LU decomposition of A ($A_k$ is the $k \times k$ upper-left part of A).
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
