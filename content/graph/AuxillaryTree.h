/**
 * Author: Kishore Kumar
 * Date: 2022-10-16
 * License: CC0
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns the root to the virtual tree stored in the class object's adj list. Tree is cleared for each query.
 * Time: $O(|S| \log |S|)$
 * Status: Tested at CodeForces
 */
#pragma once

#include "LCA.h"

struct AuxillaryTree {
    LCA &lca;
    vi &T, s; // s contains all 2k-1 nodes, useful for clearing
    vvi adj; // Take reference to this tree to solve
    AuxillaryTree(int n, LCA &mlca) : lca(mlca), T(lca.st), adj(n) {}
    void clear_tree(){ for(auto &v : s) adj[v].clear(); }
    int query(const vi &subset){
        auto cmp = [&](int a, int b) { return T[a] < T[b]; };
        clear_tree();
        s = subset; sort(all(s), cmp);
        int m = sz(s)-1;
        for(int i=0; i < m; i++) s.pb(lca.lca(s[i], s[i+1]));
        sort(all(s), cmp); s.resize(unique(all(s)) - s.begin());
        stack<int> st; st.push(s.front());
        for(int i=1; i < sz(s); i++){
            while(!lca.anc(st.top(), s[i])) st.pop();
            adj[st.top()].pb(s[i]);
            adj[s[i]].pb(st.top());
            st.push(s[i]);
        }
        return s.front();
    }
};