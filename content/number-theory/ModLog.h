/**
 * Author: Bjorn Martinsson
 * Date: 2020-06-03
 * License: CC0
 * Source: own work
 * Description: Returns the smallest $x > 0$ s.t. $a^x = b \pmod m$.
 * Time: $O(\sqrt m)$
 * Status: tested for all 0 <= a,x < 500 and 0 < m < 500.
 */
#pragma once

ll modLog(ll a, ll b, ll m) {
	ll n = (ll) sqrt(m) + 1, e = 1, f = 1, j = 1;
	unordered_map<ll, ll> A;
	while (j <= n && (e = f = e * a % m) != b % m)
		A[e * b % m] = j++;
	if (e == b % m) return j;
	if (__gcd(m, e) == __gcd(m, b)) 
		rep(i,2,n+2) if (A.count(e = e * f % m))
			return n * i - A[e];
	return LLONG_MAX;
}
