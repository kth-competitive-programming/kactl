/**
 * Author: Lukas Polacek
 * Date: 2009-10-27
 * Source: folklore
 * Description: Calculates determinant using modular arithmetics.
 * Can be rewritten to use doubles, but then use some epsilon to avoid division
 * by zero. The modulus is assumed to be a prime number. For composite moduli,
 * use CRT; for prime powers, you are on your own, but at least A is invertible iff
 * it is invertible mod p, and the identity $\det A = (\Pi^n_{k=1}(A^{-1}_k)_{k,k})^{-1}$
 * could be used on a LU decomposition of A ($A_k$ is the $k \times k$ upper-left part of A).
 * Status: tested
 * Time: $O(N^3)$
 */
#include "../number-theory/ModularArithmetic.h"

Mod det(Mod a[100][100], int n) {
	Mod res(1);
	rep(k,0,n) {
		if (a[k][k].x == 0) rep(i,k+1,n) if (a[i][k].x != 0) {
			res = res * Mod(mod - 1);
			rep(j,k,n) swap(a[k][j], a[i][j]);
			break;
		}
		if (a[k][k].x == 0) return 0;
		Mod v = a[k][k];
		rep(i,k,n) a[k][i] = a[k][i] / v;
		res = res * v;
		rep(i,k+1,n) if (a[i][k].x != 0) {
			v = Mod(0) - a[i][k];
			rep(j,k,n) a[i][j] = a[i][j] + v * a[k][j];
		}
	}
	return res;
}
