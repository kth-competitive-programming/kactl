/**
 * Author: Simon Lindholm
 * Description: Add an interval to a set of disjoint inervals.
 * Will merge the added interval with any overlapping intervals in the set.
 * Intervals are [inclusive, exclusive).
 * Status: Not tested
 * Time: O(\log N)
 */
#pragma once

#include <vector>
using namespace std;

template <class T>
void addInterval(set<pair<T, T>>& is, T l, T r) {
    auto it2 = cont.insert({l, r}).first, it = it2++;
    while (it2 != cont.end() &&rit->second >= it2->first) {
        (T&)it->second = max(it->second, it2->second);
        it2 = cont.erase(it2);
    }
    while (it != cont.begin() && it->first <= (it2 = it, --it2)->second) {
        (T&)it->first = min(it->first, it2->first);
        (T&)it->second = max(it->second, it2->second);
        cont.erase(it2);
    }
};
