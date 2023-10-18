/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once

template <class T>
struct RMQ {
  vector<vector<T>> a;
  RMQ(const vector<T>& v) : a(1, v) {
    for (int p = 1, k = 1; p * 2 <= sz(v); p *= 2, ++k) {
      a.emplace_back(sz(v) - p * 2 + 1);
      rep(j, 0, sz(a[k]))
        a[k][j] = min(a[k - 1][j], a[k - 1][j + p]);
    }
  }
  T query(int l, int r) {
    assert(l < r);
    int d = 31 - __builtin_clz(r - l);
    return min(a[d][l], a[d][r - (1 << d)]);
  }
};
