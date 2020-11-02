/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-17
 * License: CC0
 * Source: Numeriska algoritmer med matlab, Gerd Eriksson, NADA, KTH
 * Description: Finds the argument minimizing the function $f$ in the interval $[a,b]$ assuming $f$ is unimodal on the interval, i.e. has only one local minimum. The maximum error in the result is $eps$. Works equally well for maximization with a small change in the code. See TernarySearch.h in the Various chapter for a discrete version.
 * Usage:
	double func(double x) { return 4+x+.3*x*x; }
	double xmin = gss(-1000,1000,func);
 * Time: O(\log((b-a) / \epsilon))
 * Status: tested
 */
#pragma once

/// It is important for r to be precise, otherwise we don't necessarily maintain the inequality a < x1 < x2 < b.
double gss(double a, double b, double (*f)(double)) {
	double r = (sqrt(5)-1)/2, eps = 1e-7;
	double x1 = b - r*(b-a), x2 = a + r*(b-a);
	double f1 = f(x1), f2 = f(x2);
	while (b-a > eps)
		if (f1 < f2) { //change to > to find maximum
			b = x2; x2 = x1; f2 = f1;
			x1 = b - r*(b-a); f1 = f(x1);
		} else {
			a = x1; x1 = x2; f1 = f2;
			x2 = a + r*(b-a); f2 = f(x2);
		}
	return a;
}
