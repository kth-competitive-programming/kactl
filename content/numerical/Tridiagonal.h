/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-15
 * Source: Gauss
 * Description: Solves a linear equation system with a tridiagonal matrix with diagonal diag, subdiagonal sub and superdiagonal super, i.e., $x=\textrm{tridiagonal}(d,p,q,b)$ solves the equation system
$$\left(\begin{array}{c}b_0\\b_1\\b_2\\b_3\\\vdots\\b_{n-1}\end{array}\right) = 
\left(\begin{array}{cccccc}
d_0 & p_0 & 0 & 0 & \cdots & 0\\
q_0 & d_1 & p_1 & 0 & \cdots & 0\\
0 & q_1 & d_2 & p_2 & \cdots & 0\\
\vdots & \vdots & \ddots & \ddots & \ddots & \vdots\\
0 & 0 & \cdots & q_{n-3} & d_{n-2} & p_{n-2}\\
0 & 0 & \cdots & 0 & q_{n-2} & d_{n-1}\\
\end{array}\right) 
\left(\begin{array}{c}x_0\\x_1\\x_2\\x_3\\\vdots\\x_{n-1}\end{array}\right).$$

The size of diag and b should be the same and super and sub should be one element shorter. T is intended to be double. 

This is useful for solving problems on the type 
$$a_i=b_ia_{i-1}+c_ia_{i+1}+d_i,\,1\leq i\leq n,$$
where $a_0$, $a_{n+1}$, $b_i$, $c_i$ and $d_i$ are known. $a$ can then be obtained from
\begin{align*}
\{a_i\}=\textrm{tridiagonal}(&\{1,-1,-1,...,-1,1\}, \{0,c_1,c_2,\dots,c_n\},\\
&\{b_1,b_2,\dots,b_n,0\}, \{a_0,d_1,d_2,\dots,d_n,a_{n+1}\}).
\end{align*}
 * Time: O(N)
 * Status: Tested with UnitTest and UVa problem: 10014 - Simple calculations
 * Usage: int n = 1000000;
vector<double> diag(n,-1), sup(n-1,.5), sub(n-1,.5), b(n,1);
vector<double> x = tridiagonal(diag, super, sub, b);
 */
#pragma once


template <class T>
vector<T> tridiagonal(vector<T> diag, const vector<T>& super,
		const vector<T>& sub, vector<T> b) {
	rep(i,0,sz(b)-1) {
		diag[i+1] -= super[i]*sub[i]/diag[i];
		b[i+1] -= b[i]*sub[i]/diag[i];
	}
	for (int i = sz(b); --i > 0;) {
		b[i] /= diag[i];
		b[i-1] -= b[i]*super[i-1];
	}
	b[0] /= diag[0];
	return b;
}
