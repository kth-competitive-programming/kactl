/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * Source: http://en.wikipedia.org/wiki/Lucas'_theorem
 * Description: Lucas' thm: Let $m,n$ be non-negative integers and $p$ a prime. Write $m=m_kp^k+...+m_1p+m_0$ and $n=n_kp^k+...+n_1p+n_0$. Then $\binom{m}{n} \equiv \prod_{i=0}^k\binom{m_i}{n_i} \pmod{p}$.
 * Status: Untested
 * Time: O(p\log_p m)
 */
#pragma once
#include <algorithm>
#include "binomial.h"
#include "../number-theory/ModularArithmetic.h"

template<class T>
T chooseModP(T m, T n, int p) {
	Mod<T> c(1); mod = p;
	while((m || n) && c.x != 0) {
		c = c * choose<Mod<T>>(m % p, n % p);
		m /= p; n /= p;
	}
	return c.x;
}
