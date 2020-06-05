/**
 * Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Input should be a vector of (dest, global edge index), where
 * for undirected graphs, forward/backward edges have the same index.
 * Returns a list of pairs of the nodes in the Eulerian path/cycle with src at both start and end,
 * and the edge indices, or empty list if no cycle/path exists.
 * Time: O(V + E)
 * Status: stress-tested
 */
#pragma once

vector<pii> eulerWalk(const vector<vector<pii>>& gr, int nedges, int src = -1) {
  int n = sz(gr);
  if (src == -1) {
    // Find a non-isolated node.
    src = find_if(all(gr), [](const vector<pii>& v) { return !v.empty(); }) -
          begin(gr);
    if (src == n) return {};
  }

  vi D(n), its(n), eu(nedges);
  vector<pii> s = {make_pair(src, -1)};
  vector<pii> ret;
  D[src]++;  // to allow Euler paths, not just cycles
  while (!s.empty()) {
    auto x = s.back();
    int y, e, &it = its[x.first], end = sz(gr[x.first]);
    if (it == end) {
      ret.emplace_back(x);
      s.pop_back();
      continue;
    }
    tie(y, e) = gr[x.first][it++];
    if (!eu[e]) {
      D[x.first]--, D[y]++;
      eu[e] = 1;
      s.emplace_back(y, e);
    }
  }
  for (int x : D)
    if (x < 0) return {};
  if (sz(ret) != nedges + 1) return {};
  reverse(all(ret));
  return ret;
}
