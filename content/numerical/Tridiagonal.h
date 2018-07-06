/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-15
 * License: CC0
 * Source: Gauss
 * Description: $x=\textrm{tridiagonal}(d,p,q,b)$ solves the equation system
\[
\left(\begin{array}{c}b_0\\b_1\\b_2\\b_3\\\vdots\\b_{n-1}\end{array}\right) =
\left(\begin{array}{cccccc}
d_0 & p_0 & 0 & 0 & \cdots & 0\\
q_0 & d_1 & p_1 & 0 & \cdots & 0\\
0 & q_1 & d_2 & p_2 & \cdots & 0\\
\vdots & \vdots & \ddots & \ddots & \ddots & \vdots\\
0 & 0 & \cdots & q_{n-3} & d_{n-2} & p_{n-2}\\
0 & 0 & \cdots & 0 & q_{n-2} & d_{n-1}\\
\end{array}\right)
\left(\begin{array}{c}x_0\\x_1\\x_2\\x_3\\\vdots\\x_{n-1}\end{array}\right).
\]

This is useful for solving problems on the type
\[ a_i=b_ia_{i-1}+c_ia_{i+1}+d_i,\,1\leq i\leq n, \]
where $a_0$, $a_{n+1}$, $b_i$, $c_i$ and $d_i$ are known. $a$ can then be obtained from
\begin{align*}
\{a_i\}=\textrm{tridiagonal}(&\{1,-1,-1,...,-1,1\}, \{0,c_1,c_2,\dots,c_n\},\\
&\{b_1,b_2,\dots,b_n,0\}, \{a_0,d_1,d_2,\dots,d_n,a_{n+1}\}).
\end{align*}
Warning: might fail if numbers are not nice. If so, perturb them slightly.
 * Time: O(N)
 * Status: Usually works...
 */
#pragma once

typedef double T;
vector<T> tridiagonal(vector<T> diag, const vector<T>& super,
		const vector<T>& sub, vector<T> b) {
	rep(i,0,sz(b)-1) {
		diag[i+1] -= super[i]*sub[i]/diag[i];
		b[i+1] -= b[i]*sub[i]/diag[i];
	}
	for (int i = sz(b); i--;) {
		b[i] /= diag[i];
		if (i) b[i-1] -= b[i]*super[i-1];
	}
	return b;
}
