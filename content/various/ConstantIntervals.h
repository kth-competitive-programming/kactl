/**
 * Author: Simon Lindholm
 * Date: 2015-03-20
 * License: CC0
 * Source: me
 * Description: Split a monotone function on [from, to) into a minimal set of half-open intervals on which it has the same value.
 *  Runs a callback g for each such interval.
 * Usage: constantIntervals(0, sz(v), [\&](ll x){return v[x];}, [\&](ll lo, ll hi, T val){...});
 * Time: O(k\log\frac{n}{k})
 * Status: tested
 */
#pragma once

template<class F, class G, class T>
void rec(ll from, ll to, F& f, G& g, ll& i, T& p, T q) {
	if (p == q) return;
	if (from == to) {
		g(i, to, p);
		i = to; p = q;
	} else {
		ll mid = (from + to) >> 1;
		rec(from, mid, f, g, i, p, f(mid));
		rec(mid+1, to, f, g, i, p, q);
	}
}
template<class F, class G>
void constantIntervals(ll from, ll to, F f, G g) {
	if (to <= from) return;
	ll i = from; auto p = f(i), q = f(to-1);
	rec(from, to-1, f, g, i, p, q);
	g(i, to, q);
}
