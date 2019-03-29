/**
 * Author: chilli, c1729
 * Date: 2019-03-28
 * License: CC0
 * Description: Deterministic Miller-Rabin primality test. Numbers taken from 
 * Time: 7 times the complexity of $a^b \mod c$.
 */
#pragma once

#include "ModMulLL.h"

bool prime(ull n) {
    vector<ull> cs({2, 325, 9375, 28178, 450775, 9780504, 1795265022});
    if (n <= 1) return false;
    for (ull p : {2, 3, 5, 13, 19, 73, 193, 407521, 299210837})
        if (n % p == 0) return (n == p);
    ull d = n - 1, s = 0;
    while (!(d & 1)) d >>= 1, s++;
    return !any_of(all(cs), [&](ull a) {
        for (ull i = 0, p = mod_pow(a, d, n); i < s; i++, p = mod_mul(p, p, n))
            if (p == n - 1 || (i == 0 && p == 1))
                return false;
        return true;
    });
}
