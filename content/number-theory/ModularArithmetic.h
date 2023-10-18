/**
 * Author: Lukas Polacek, FHVirus
 * Date: 2023-10-12
 * License: CC0
 * Source: folklore, old KACTL
 * Description: Operators for modular arithmetic.
 */
#pragma once

#include "Euclid.h"
template <class T, T mod>
struct mint {
  // static int MOD = mod; for dynamic mod
  T v;
  mint(T v = 0) : v(v + ((v < 0) - (v >= mod)) * mod) {}
  mint operator+(mint o) { return mint(v + o.v); }
  mint operator-(mint o) { return mint(v - o.v); }
  mint operator*(mint o) // maybe __int128_t
  { return mint((T) ((ll) v * o.v % mod)); }
  mint operator/(mint o) { return *this * o.inv(); }
  mint inv() {
    T x, y, g = euclid(v, mod, x, y);
    assert(g == 1); return mint(x);
  }
  mint pow(ll e) {
    mint r(1), x(*this);
    for (; e; e >>= 1, x = x * x)
      if (e & 1) r = r * x;
    return r;
  }
  T val() { return v; }
};
using mi = mint<int, 998244353>;
