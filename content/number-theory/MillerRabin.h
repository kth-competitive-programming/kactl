/**
 * Author: chilli, c1729
 * Date: 2019-03-28
 * License: CC0
 * Description: Deterministic Miller-Rabin primality test. Works for numbers up to 2^64
 * Time: 7 times the complexity of $a^b \mod c$.
 */
#pragma once

#include "ModMulLL.h"

bool isPrime(ull n) {
    if (n <= 1) return false;
    for (ull p : {2, 3, 5, 13, 19, 73, 193, 407521, 299210837})
        if (n % p == 0) return (n == p);
    ull d = n - 1;
    while (!(d & 1)) d >>= 1;
    for (ull a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        ull p = mod_pow(a, d, n), i = d;
        while (p != n - 1 && i != n - 1 && p != 1)
            i <<= 1, p = mod_mul(p, p, n);
        if (i == n - 1 && i > d) return false;
    }
    return true;
}
