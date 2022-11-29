/**
 * Author: Kishore Kumar
 * Date: 2022-10-15
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure. 
 * dsu[v] holds -size(v) if v is parent, else contains parent id
 * Time: $O(\alpha(N))$
 */
#pragma once

struct DSU{
    vi dsu;
    int num_comps;
    DSU(int n) : dsu(n, -1), num_comps(n) {}
    int parent(int i){ return dsu[i] < 0 ? i : dsu[i] = parent(dsu[i]); }
    int size(int i) { return -dsu[parent(i)]; }
    int operator[](int i){ return parent(i); }
    void unify(int a, int b){
        a = parent(a), b = parent(b);
        if(dsu[a] > dsu[b]) swap(a, b);
        if(a!=b) dsu[a] += dsu[b], dsu[b] = a, num_comps--;
    }
};