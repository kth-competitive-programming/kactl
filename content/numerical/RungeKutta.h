/**
 * Author: Tyler Marks
 * Description: Numerically approximates the solution to a system of Differential Equations
 * Status: Tested on 2020 Northern Eurasia: Hit the Hay
 */
#pragma once

template<class F, class T>
T solveSystem(F f, T x, double time, int iters) {
	double h = time / iters;
	for(int iter = 0; iter < iters; iter++) {
		T k1 = f(x);
		A k2 = f(x + 0.5 * h * k1);
		A k3 = f(x + 0.5 * h * k2);
		A k4 = f(x + h * k3);
		x = x + h / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
	}
	return x;
}