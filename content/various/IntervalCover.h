/**
 * Author: Johan Sannemo
 * Description: Compute indices of smallest set of intervals covering another interval.
 * Intervalls should be [inclusive, exclusive). To support [inclusive, inclusive),
 * change (A) to add || R.empty().
 * Time: O(N \log N)
 * Status: Tested on Kattis, intervalcover
 */
#pragma once

#include <vector>
using namespace std;

template<class T>
vi cover(pair<T, T> G, vector<pair<T, T>> I) {
    vi S(sz(I)), R;
    iota(all(S), 0);
    sort(all(S), [&](int a, int b) { return I[a] < I[b]; });
    T cur = G.first;
    int at = -1;
    while (cur < G.second) { // (A)
        pair<T, int> mx = make_pair(cur, -1);
        while (at + 1 < sz(I) && I[S[at + 1]].first <= cur) {
            at++;
            mx = max(mx, make_pair(I[S[at]].second, S[at]));
        }
        if (mx.second == -1) return {};
        cur = mx.first;
        R.push_back(mx.second);
    }
    return R;
}
