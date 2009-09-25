/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * Source: http://en.wikipedia.org/wiki/Lucas'_theorem
 * Description: \emph{Lucas' thm}: Let $m,n$ be non-negative integers and $p$ a prime. Write $m=m_kp^k+...+m_1p+m_0$ and $n=n_kp^k+...+n_1p+n_0$. Then $\binom{m}{n} \equiv \prod_{i=0}^k\binom{m_i}{n_i} \pmod{p}$.
 * Status: Untested
 * Time: O(p\log_p\max(m,n))
 */
#pragma once
#include <algorithm>
#include "binomial.h"

template<class T>
T chooseModP(int m, int n, int p) {
	T c = 1;
	while((m||n) && c) {
		c*=choose<T>(m%p,n%p);
		c%=p; m/=p; n/=p;
	}
	return c;
}
