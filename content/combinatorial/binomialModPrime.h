/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Lucas'_theorem
 * Description: Lucas' thm: Let $n,m$ be non-negative integers and $p$ a prime.
 * Write $n=n_kp^k+...+n_1p+n_0$ and $m=m_kp^k+...+m_1p+m_0$.
 * Then $\binom{n}{m} \equiv \prod_{i=0}^k\binom{n_i}{m_i} \pmod{p}$.
 * fact and invfact must hold pre-computed factorials / inverse factorials, e.g. from ModInverse.h.
 * Status: Untested
 * Time: O(\log_p n)
 */
#pragma once

ll chooseModP(ll n, ll m, int p, vi& fact, vi& invfact) {
	ll c = 1;
	while (n || m) {
		ll a = n % p, b = m % p;
		if (a < b) return 0;
		c = c * fact[a] % p * invfact[b] % p * invfact[a - b] % p;
		n /= p; m /= p;
	}
	return c;
}
