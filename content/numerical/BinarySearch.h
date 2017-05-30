/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-07
 * License: CC0
 * Source: Common sense
 * Description: Finds a zero point of f on the interval [a b]. f(a) must be less than 0 and f(b) greater than 0. Useful for solving equations like kx=sin(x) as in the example below.
 * Status: tested
 * Usage:
	double func(double x) { return .23*x-sin(x); }
	double x0 = bs(0,4,func);
 * Time: O(\log((b-a) / \epsilon))
 */
#pragma once

double bs(double a, double b, double (*f)(double)) {
	//for(int i = 0; i < 60; ++i){
	while (b-a > 1e-6) {
		double m = (a+b)/2;
		if (f(m) > 0) b = m;
		else a = m;
	}
	return a;
}
