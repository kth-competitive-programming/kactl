/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "euclid.h"
const ll mod = 17; // change to something else
struct mint {
    ll x;
    mint(ll x = 0) : x(x){}
    mint operator+(mint b) { return mint(x + b.x >= mod ? x + b.x - mod : x + b.x); }
    mint operator-(mint b) { return mint(x - b.x < 0 ? x - b.x + mod : x - b.x); }
    mint operator*(mint b) { return mint(x * b.x % mod); }
    mint operator/(mint b) { return *this * invert(b); }
    mint invert(mint a) {
        ll x, y, g = euclid(a.x, mod, x, y);
        assert(g == 1); return mint(x < 0 ? x + mod : x);
    }
    mint operator^(ll e) {
        if(!e) return mint(1);
        mint r = *this ^ (e / 2); r = r * r;
        return e&1 ? *this * r : r;
    }
    ll val() { return x; }
};
