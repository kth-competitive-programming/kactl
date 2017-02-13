/**
 * Author: Simon Lindholm
 * Description: Add and remove intervals from a set of disjoint intervals.
 * Will merge the added interval with any overlapping intervals in the set when adding.
 * Intervals are [inclusive, exclusive).
 * Status: Tested, manually
 * Time: O(\log N)
 */
#pragma once

#include <vector>
using namespace std;

template <class T>
void addInterval(set<pair<T, T>>& is, T l, T r) {
	if (l == r) return;
	auto it2 = is.insert({l, r}).first, it = it2++;
	while (it2 != is.end() && it->second >= it2->first) {
		(T&)it->second = max(it->second, it2->second);
		it2 = is.erase(it2);
	}
	while (it != is.begin() && it->first <= (it2 = it, --it2)->second) {
		(T&)it->first = min(it->first, it2->first);
		(T&)it->second = max(it->second, it2->second);
		is.erase(it2);
	}
};

template <class T>
void removeInterval(set<pair<T, T>>& is, T l, T r) {
	if (l == r) return;
	addInterval(is, l, r);
	auto it = --is.upper_bound({l, numeric_limits<T>::max()});
	T r2 = it->second;
	if (it->first == l) is.erase(it);
	else (T&)it->second = l;
	if (r != r2) is.emplace(r, r2);
};
