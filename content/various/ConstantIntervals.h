/**
 * Author: Simon Lindholm
 * Date: 2015-03-20
 * Source: me
 * Description: Split a monotone function on [from, to) into a minimal set of half-open intervals on which it has the same value.
 * Usage: constantIntervals(0, sz(v), [\&](int x){return v[x];});
 * Time: O(k\log\frac{n}{k})
 * Status: tested
 */
#pragma once
#include <vector>
#include <map>
using namespace std;

typedef vector<pii> vpii;

template<class F, class T>
void rec(int from, int to, F f, vpii& ret, int& i, T& p, T q) {
	if (p == q) return;
	if (from == to) {
		ret.emplace_back(i, to);
		i = to; p = q;
	} else {
		int mid = (from + to) >> 1;
		rec(from, mid, f, ret, i, p, f(mid));
		rec(mid+1, to, f, ret, i, p, q);
	}
}
template<class F>
vpii constantIntervals(int from, int to, F f) {
	vpii ret;
	if (to <= from) return ret;
	int i = from; auto p = f(i);
	rec(from, to-1, f, ret, i, p, f(to-1));
	ret.emplace_back(i, to);
	return ret;
}
