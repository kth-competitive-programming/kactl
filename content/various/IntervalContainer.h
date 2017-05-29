/**
 * Author: Simon Lindholm
 * License: CC0
 * Description: Add and remove intervals from a set of disjoint intervals.
 * Will merge the added interval with any overlapping intervals in the set when adding.
 * Intervals are [inclusive, exclusive).
 * Status: fuzz-tested
 * Time: O(\log N)
 */
#pragma once


template <class T>
auto addInterval(set<pair<T, T>>& is, T L, T R) {
	if (L == R) return is.end();
	auto it = is.lower_bound({L, R}), before = it;
	while (it != is.end() && it->first <= R) {
		R = max(R, it->second);
		before = it = is.erase(it);
	}
	if (it != is.begin() && (--it)->second >= L) {
		L = min(L, it->first);
		R = max(R, it->second);
		is.erase(it);
	}
	return is.insert(before, {L,R});
};

template <class T>
void removeInterval(set<pair<T, T>>& is, T L, T R) {
	if (L == R) return;
	auto it = addInterval(is, L, R);
	T r2 = it->second;
	if (it->first == L) is.erase(it);
	else (T&)it->second = L;
	if (R != r2) is.emplace(R, r2);
};
