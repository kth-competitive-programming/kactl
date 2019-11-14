/**
 * Author: Andrei Navumenka, chilli
 * Date: 2019-11-08
 * License: Unlicense
 * Source: https://github.com/indy256/codelibrary/blob/master/cpp/numbertheory/discrete_log.cpp
 * Description: Returns the smallest $x \ge 0$ s.t. $a^x = b \pmod m$. a and m must be coprime.
 * Time: $O(\sqrt m)$
 * Status: tested for all 0 <= a,x,m < 200.
 */
#pragma once

ll modLog(ll a, ll b, ll m) {
	assert(__gcd(a, m) == 1);
	ll n = (ll) sqrt(m) + 1, e = 1, x = 1, res = LLONG_MAX;
	unordered_map<ll, ll> f;
	rep(i,0,n) e = e * a % m;
	rep(i,0,n) x = x * e % m, f.emplace(x, i + 1);
	rep(i,0,n) if (f.count(b = b * a % m))
		res = min(res, f[b] * n - i - 1);
	return res;
}
