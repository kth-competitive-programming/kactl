/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-17
 * Source: Numeriska algoritmer med matlab, Gerd Eriksson, NADA, KTH
 * Description: Finds the argument minimizing the function $f$ in the interval $[a,b]$ assuming $f$ is unimodal on the interval, i.e. has only one local minima. The maximum error in the result is $e$. Works equaly well for maximization with a small change in the code.
 * Status: tested
 * Usage:
	double func(double x) { return 4+x+.3*x*x; }
	double xmin = gss(-1000,1000,func);
	double pi = gss(0,6,cos);
 * Time: $O\left(\log\left(\frac{b-a}{e}\right)\right)$
 */
#pragma once

double gss(double a, double b, double (*f)(double), 
		double e = 1e-6) {
	double r = (sqrt(5)-1)/2; //=.618...=golden ratio-1
	double x1 = b-r*(b-a), x2 = a+r*(b-a);
	double f1 = f(x1), f2 = f(x2);
	while (b-a > e) {
		if (f1 < f2) { //change to > to find maximum
			b = x2; x2 = x1; f2 = f1;
			x1 = b-r*(b-a); f1 = f(x1);
		} else {
			a = x1; x1 = x2; f1 = f2;
			x2 = a+r*(b-a); f2 = f(x2);
		}
	}
	return a;
}
