/**
 * Author: Tyler Marks
 * Description: Makes Jacobian Matrix using finite differences
 * Status: stress-tested on GNY Arthur's Table
 */
#pragma once

template<class F, class T>
vector<vector<T>> makeJacobian(F &f, vector<T> &x) {
	int n = sz(x);
	vector<vector<T>> J(n, vector<T>(n));
	vector<T> fX0 = f(x);
	rep(i, 0, n) { 
		x[i] += eps;
		vector<T> fX1 = f(x);
		rep(j, 0, n){
			J[j][i] = (fX1[j] - fX0[j]) / eps;
		}
		x[i] -= eps;
	}
	return J;
}