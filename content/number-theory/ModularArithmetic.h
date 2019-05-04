/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

const ll mod = 17; // change to something else
struct Mod {
    ll v;
    Mod() : v(0) {}
    Mod(ll vv) : v(vv % mod) {}
    Mod operator+(Mod b) { return Mod((v + b.v) % mod); }
    Mod operator-(Mod b) { return Mod(v - b.v + mod); }
    Mod operator*(Mod b) { return Mod(v * b.v); }
    Mod operator/(Mod b) { return *this * invert(b); }
	Mod invert(Mod a) { return a^(mod-2); }
	Mod operator^(ll e) {
        ll ans = 1, b = (*this).v;
        for (; e; b = b * b % mod, e /= 2)
            if (e & 1) ans = ans * b % mod;
        return ans;
	}
    explicit operator ll() const { return v; }
};