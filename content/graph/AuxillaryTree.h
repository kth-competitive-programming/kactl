/**
 * Author: Kishore Kumar
 * Date: 2022-10-16
 * License: CC0
 * ExtDesc: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns the root to the virtual tree stored in the class object's adj list. Tree is cleared for each query.
 * $O(|S| \log |S|)$
 * Description: Returns root to vtree. Auto-cleared per query. $O(|S| \log |S|)$
 * Status: Tested at CodeForces
 */
#pragma once

#include "../data-structures/RMQ.h"
#include "LCA.h"

struct AuxillaryTree {
    LCA &lca;
    vi &T, s; // s contains all 2k-1 nodes, useful for clearing
    vvi adj; // Take reference to this tree to solve
    AuxillaryTree(int n, LCA &L) : lca(L), T(lca.st), adj(n) {}
    void clear_tree(){ for(auto &v : s) adj[v].clear(); }
    int query(const vi &subset){
        auto cmp = [&](int a, int b) { return T[a] < T[b]; };
        clear_tree(); s = subset; sort(all(s), cmp);
        for(int i=0; i < sz(s)-1; i++) s.pb(lca.lca(s[i], s[i+1]));
        sort(all(s), cmp); s.resize(unique(all(s))-s.begin());
        stack<int> st; st.push(s.front());
        for(int i=1; i < sz(s); st.push(s[i++])){
            while(!lca.anc(st.top(), s[i])) st.pop();
            adj[st.top()].pb(s[i]); adj[s[i]].pb(st.top());
        }
        return s.front();
    }
};