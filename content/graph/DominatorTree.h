/**
 * Author: FHVirus
 * Date: 2023-08-20
 * License: CC0
 * Source: ckiseki and original paper
 * Description: Build dominator tree of graph adj. 0 base.
 * Root's dominator is itself, and unreachable nodes have
 * -1 as dominator.
 * Time: $O(M \log N)$
 * Status: tested at yosupo judge & codeforces 100513L
 */
#pragma once

struct DominatorTree {
  vi p, semi, ord, dom, f, val;
  vector<vi> adj, pre, bkt;
  void dfs(int u) {
    semi[u] = sz(ord);
    ord.push_back(u);
    for (int v : adj[u]) {
      if (semi[v] == -1) p[v] = u, dfs(v);
      pre[v].push_back(u);
    }
  }
  int eval(int u, int t = 0) {
    if (f[u] == -1) return t ? -1 : u;
    if (int p = eval(f[u], 1); p != -1) {
      if (semi[val[f[u]]] < semi[val[u]])
        val[u] = val[f[u]];
      f[u] = p;
      return t ? p : val[u];
    } return t ? f[u] : val[u];
  }
  DominatorTree(int N, const vector<vi>& adj, int r): p(N, -1), 
  semi(p), dom(p), f(p), val(N), adj(adj), pre(N), bkt(N) {
    iota(all(val), 0);
    dfs(r);
    for (int i = sz(ord); --i; ) {
      int u = ord[i];
      for (int v : pre[u])
        semi[u] = min(semi[u], semi[eval(v)]);
      bkt[ord[semi[u]]].push_back(u);
      f[u] = p[u];
      for (int v : bkt[p[u]]) {
        int w = eval(v);
        dom[v] = semi[w] < semi[v] ? w : p[u];
      }
      bkt[p[u]].clear();
    }
    dom[r] = r;
    for (int u: ord) if (dom[u] != ord[semi[u]])
      dom[u] = dom[dom[u]];
  }
};
