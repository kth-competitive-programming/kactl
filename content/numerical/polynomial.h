/**
* Author:
* Date: 2010-11-18
* Source: tinyKACTL
* Description:
*/
#pragma once

#include <vector>
using namespace std;

struct polynomial {
	int n; vector<double> a;
	polynomial(int n): n( n), a(n+1) {}
	double operator()(double x) const { // Calc value at x
		double val = 0;
		for(int i = n; i >= 0; --i) (val *= x) += a[i];
		return val;
	}
	void diff() { // differentiate
		for(int i = 1; i <= n; ++i) a[i-1] = i*a[i];
		a.pop_back(); --n;
	}
	void divroot(double x0) { // divide by (x-x0), ignore remainder
		double b = a.back(), c; a.back() = 0;
		for(int i=n--; i--;) c = a[i], a[i] = a[i+1]*x0+b, b=c;
		a.pop_back();
	}
};
