/**
 * Author: Tyler Marks
 * Description: Gets area under a curve
 * Status: tested on NEERC Damage Assessment
 */
#pragma once

#define approx(a, b) (b-a) / 6 * (f(a) + 4 * f((a+b) / 2) + f(b))

template<class F>
ld adapt (F &f, ld a, ld b, ld A, int iters) {
	ld m = (a+b) / 2;
	ld A1 = approx(a, m), A2 = approx(m, b);
	if(!iters && (abs(A1 + A2 - A) < eps || b-a < eps))
		return A;
	ld left = adapt(f, a, m, A1, max(iters-1, 0));
	ld right = adapt(f, m, b, A2, max(iters-1, 0));
	return left + right;
}

template<class F>
ld integrate(F f, ld a, ld b, int iters = 0) {
	return adapt(f, a, b, approx(a, b), iters);
}