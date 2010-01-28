/**
 * Author: Lukas Polacek
 * Date: 2010-01-26
 * Source: TopCoder tutorial
 * Description: Calculate $a^b\bmod c$.
 */
#pragma once

typedef unsigned long long ull;
const int bits = 10;
//if all numbers are less than 2^k, set bits = 64-k
const ull po = 1 << bits;
ull mulmod(ull a, ull b, ull &c) {
	ull x = a * (b & (po - 1)) % c;
	while ((b >>= bits) > 0) {
		a = (a << bits) % c;
		x += (a * (b & (po - 1))) % c;
	}
	return x % c;
}
ull mod_pow(ull a, ull b, ull mod) {
	if (b == 0) return 1;
	ull res = mod_pow(a, b / 2, mod);
	res = mulmod(res, res, mod);
	if (b & 1) return mulmod(res, a, mod);
	return res;
}
