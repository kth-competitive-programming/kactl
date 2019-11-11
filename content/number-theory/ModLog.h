/**
 * Author: Andrei Navumenka, chilli
 * Date: 2019-11-08
 * License: Unlicense
 * Source: https://github.com/indy256/codelibrary/blob/master/cpp/numbertheory/discrete_log.cpp
 * Description: Calculates the discrete log. Returns an x s.t. a^x = b mod m. a and m must be coprime.
 * Time: $O(m^{1/2})$
 * Status: tested for all values under a 1000 for a,x, and m.
 */
#pragma once

ll modLog(ll a, ll b, ll m) {
	assert(__gcd(a, m) == 1);
	if (b == 1) return 0;
	ll n = (ll) sqrt(m) + 1, e = 1;
	rep(i,0,n) e = e * a % m;
	unordered_map<ll, ll> f;
	for (ll i=1, x = e; i<=n; i++, x = x*e%m) f.emplace(x, i);
	for (ll i = 0, x = b; i <= n; i++, x = x * a % m)
		if (f.count(x)) return f[x] * n - i;
	return -1;
}
