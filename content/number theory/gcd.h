/**
 * Author:
 * Date:
 * Source: tinyKACTL
 * Description:
 */
#pragma once

int gcd(int a, int b) {
  return b==0?a:gcd(b, a%b);
}

// Finds x and y s.t. a*x+b*y=gcd(a,b)
// If a and b are coprime, then x is the inverse of a mod b.
int euclid(int a, int b, int &x, int &y) {
	if (b) { int d=euclid(b, a%b, y, x);
		return y-=a/b*x, d; }
	return x=1, y=0, a;
}
