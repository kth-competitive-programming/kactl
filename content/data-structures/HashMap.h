/**
 * Author: Simon Lindholm
 * Date: 2018-07-23
 * License: CC0
 * Source: http://codeforces.com/blog/entry/60737
 * Description: Hash map with the same API as unordered\_map, but \tilde 3x faster.
 * Initial capacity must be a power of 2 (if provided).
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
__gnu_pbds::gp_hash_table<ll, int> h({},{},{},{}, {1 << 16});

/** For CodeForces, or other places where hacking might be a problem:
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(ll x) const { return x ^ RANDOM; }
};
__gnu_pbds::gp_hash_table<ll, int, chash> h({},{},{},{}, {1 << 16});
*/
