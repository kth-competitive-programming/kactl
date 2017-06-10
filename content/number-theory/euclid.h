/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds the Greatest Common Divisor to the integers $a$ and $b$. Euclid also finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
#pragma once

ll gcd(ll a, ll b) { return __gcd(a, b); }

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (b) { ll d = euclid(b, a % b, y, x);
		return y -= a/b * x, d; }
	return x = 1, y = 0, a;
}
