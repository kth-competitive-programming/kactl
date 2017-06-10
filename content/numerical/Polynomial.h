/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
 * Description:
 */
#pragma once

struct Polynomial {
	int n; vector<double> a;
	Polynomial(int n): n(n), a(n+1) {}
	double operator()(double x) const {
		double val = 0;
		for(int i = n; i >= 0; --i) (val *= x) += a[i];
		return val;
	}
	void diff() {
		rep(i,1,n+1) a[i-1] = i*a[i];
		a.pop_back(); --n;
	}
	void divroot(double x0) {
		double b = a.back(), c; a.back() = 0;
		for(int i=n--; i--;) c = a[i], a[i] = a[i+1]*x0+b, b=c;
		a.pop_back();
	}
};
