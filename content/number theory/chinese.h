/**
 * Author:
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: Chinese Remainder Theorem
 * Status: Works
 * Usage: chinese(a, m, b, n) returns a number $x$, such that
 * $x\equiv a \pmod m$ and $x\equiv b \pmod n$. For not
 * coprime $n, m$, use chinese_common. Note that all numbers must be less than
 * $2^{31}$.
 * Time: $\log(m + n)$
 */
#include "euclid.h"

template <class Z> inline Z chinese(Z a, Z m, Z b, Z n) {
	Z x, y; euclid(m, n, x, y);
	return a * (y + m) % m * n + b * (x + n) % n * m;
}

template <class Z> inline Z chinese_common(Z a, Z m, Z b, Z n) {
	Z d = gcd(m, n);
	if (((b -= a) %= n) < 0) b += n;
	if (b % d) return -1; // No solution
	return d * chinese(Z(0), m/d, b/d, n/d) + a;
}
