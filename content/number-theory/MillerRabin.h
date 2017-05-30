/**
 * Author: Lukas Polacek
 * Date: 2010-01-26
 * License: CC0
 * Source: TopCoder tutorial
 * Description: Miller-Rabin primality probabilistic test.
 * Probability of failing one iteration is at most 1/4. 15 iterations should be
 * enough for 50-bit numbers.
 * Time: 15 times the complexity of $a^b \mod c$.
 */
#pragma once

#include "ModMulLL.h"

bool prime(ull p) {
	if (p == 2) return true;
	if (p == 1 || p % 2 == 0) return false;
	ull s = p - 1;
	while (s % 2 == 0) s /= 2;
	rep(i,0,15) {
		ull a = rand() % (p - 1) + 1, tmp = s;
		ull mod = mod_pow(a, tmp, p);
		while (tmp != p - 1 && mod != 1 && mod != p - 1) {
			mod = mod_mul(mod, mod, p);
			tmp *= 2;
		}
		if (mod != p - 1 && tmp % 2 == 0) return false;
	}
	return true;
}
