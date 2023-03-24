/**
 * Author: Simon Lindholm, chilli
 * Date: 2018-07-23
 * License: CC0
 * Source: http://codeforces.com/blog/entry/60737
 * Description: 3x faster. Uses 1.5x memory.
 */
#pragma once
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds; 
struct chash {
    using u64 = uint64_t;
    const u64 R = (u64)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned h32(unsigned x) {
        x = (x ^ (x >> 16)) * 0x45d9f3b, x = (x ^ (x >> 16)) * 0x45d9f3b; return x ^ (x >> 16); }
    static u64 sm64(u64 x) {
        x += 0x9e3779b97f4a7c15, x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9, x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31); }
    template<typename T>
    u64 operator()(T x) const { return sizeof(x) <= 4 ? h32(unsigned(x ^ R)) : (sm64(x) ^ R); } };
 using hash_table = gp_hash_table<int, int, chash>;