/**
 * Author: Tyler Marks
 * Description: Solves a system on non-linear equations
 * Status: stress-tested on GNY Arthur's Table
 */
#pragma once

#include jacobianMatrix.h

template<class F, class T>
void solveNonlinear(F f, vector<T> &x){
	int n = sz(x);
	rep(iter, 0, 100) {
		vector<vector<T>> J = makeJacobian(f, x);
		matInv(J);
		vector<T> dx = J * f(x);
		x = x - dx;
	}
}