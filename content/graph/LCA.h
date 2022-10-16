/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected. Also supports path dist. and isAncestor queries in constant time.
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/RMQ.h"

struct LCA {
    int T = 0;
    vi st, path, ret; vi en, d;
    RMQ<int> rmq;
    LCA(vector<vi>& C) : st(sz(C)), en(sz(C)), d(sz(C)), rmq((dfs(C,0,-1), ret)) {}
    void dfs(vvi &adj, int v, int par) {
        st[v] = T++;
        for (auto to : adj[v]) if (to != par) {
            path.pb(v), ret.pb(st[v]);
            d[to] = d[v] + 1;
            dfs(adj, to, v);
        }
        en[v] = T-1;
    }
    bool anc(int p, int c) { return st[p] <= st[c] and en[p] >= en[c]; }
    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(st[a], st[b]);
        return path[rmq.query(a, b-1)];
    }
    int dist(int a, int b) { return d[a] + d[b] - 2*d[lca(a,b)]; }
};
