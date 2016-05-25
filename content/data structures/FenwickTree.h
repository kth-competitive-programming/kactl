/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * Source: folklore/TopCoder
 * Description: In the beginning there is an array $a[n]$ full of zeroes.
 * Fenwick tree can be used to retrieve sum $a[i]$ over any half-open interval $[0, x)$. You
 * can also update the value $a[x]$ (update function takes the difference
 * between the old and new value).
 * Time: Both operations are $O(\log N)$.
 */
#pragma once
#include <vector>
using namespace std;

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1)
			s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1)
			res += s[pos-1];
		return res;
	}
};
