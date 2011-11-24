/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 * Time: Division is O(\log mod), everything else is O(1).
 */
#include <vector>
#include "euclid.h"

int mod = 17;//change to something else
template<class Z> struct Mod {
	Z x;
	Mod(Z xx) : x(xx) {}
	Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
	Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
	Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
	Z inver(Z a) {
		Z x, y;
		euclid(a, Z(mod), x, y);
		return (mod + x) % mod;
	}
	Mod operator/(Mod b) {
		return Mod((x * inver(b.x)) % mod);
	}
};
