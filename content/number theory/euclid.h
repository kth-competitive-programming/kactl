/**
 * Author: Håkan Terelius
 * Date: 2009-08-26
 * Source: tinyKACTL
 * Description: Finds the Greatest Common Divisor to the integers $a$ and $b$. Euclid also finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
#pragma once

int gcd(int a, int b) {
  return b==0?a:gcd(b, a%b);
}

template <class Z> 
Z euclid(Z a, Z b, Z &x, Z &y) {
	if (b) {  Z d = euclid(b, a % b, y, x);
		return y -= a/b * x, d;  }
	return x = 1, y = 0, a;
}
