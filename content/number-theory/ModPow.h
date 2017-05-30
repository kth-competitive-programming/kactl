/**
 * Author: Simon Lindholm
 * Date: 2016-09-10
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
#pragma once

const ll mod = 1000000007; // faster if const
ll modpow(ll a, ll e) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1);
	return e & 1 ? x * a % mod : x;
}
