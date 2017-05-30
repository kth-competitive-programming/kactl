/**
 * Author: Simon Lindholm
 * Date: 2017-05-10
 * License: CC0
 * Source: Wikipedia
 * Description: Given $n$ points (x[i], y[i]), computes an n-1-degree polynomial $p$ that
 *  passes through them: $p(x) = a[0]*x^0 + ... + a[n-1]*x^{n-1}$.
 *  For numerical precision, pick $x[k] = c*\cos(k/(n-1)*\pi), k=0 \dots n-1$.
 * Time: O(n^2)
 */
#pragma once

typedef vector<double> vd;
vd interpolate(vd x, vd y, int n) {
	vd res(n), temp(n);
	rep(k,0,n-1) rep(i,k+1,n)
		y[i] = (y[i] - y[k]) / (x[i] - x[k]);
	double last = 0; temp[0] = 1;
	rep(k,0,n) rep(i,0,n) {
		res[i] += y[k] * temp[i];
		swap(last, temp[i]);
		temp[i] -= last * x[k];
	}
	return res;
}
