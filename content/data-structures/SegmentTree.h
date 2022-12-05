/**
 * Author: Kishore Kumar
 * Date: 2022-10-15
 * License: CC0
 * Source: https://codeforces.com/blog/entry/18051
 * Description: modular iterative segtree. Inclusive bounds [L, R]. Pass merge function as lambda.
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

template <typename T, typename F>
struct Segtree{
    int n; vector<T> tree;
    T identity; F merge;
    Segtree(const vector<T> &arr, T id, F _m) : n(sz(arr)), tree(2*n), identity(id), merge(_m){
        for(int i=0; i<n; i++) tree[n+i] = arr[i];
        for(int i=n-1; i>=1; i--) 
            tree[i] = merge(tree[2*i], tree[2*i+1]);
    }
    T query(int l, int r){
        T res = identity; assert(l >= 0 and r < n and l <= r);
        for(l += n, r += n; l <= r; l>>=1, r>>=1){
            if(l == r) return merge(res, tree[l]);
            if(l&1) res = merge(res, tree[l++]);
            if(!(r&1)) res = merge(res, tree[r--]);
        }
        return res;
    }
    void update(int v, T value){
        assert(v >= 0 and v < n);
        for(tree[v+=n] = value; v > 1; v >>= 1)
            tree[v>>1] = merge(tree[v], tree[v^1]);
    }
};

// Usage
auto merge = [&](int a, int b) { return min(a, b); };
Segtree<int, decltype(merge)> st(arr, INT_MAX, merge);

