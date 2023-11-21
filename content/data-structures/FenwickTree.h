/**
 * Author:
 * Description: 0-indexed. (1-index for internal bit trick)
 * Usage: FenwickTree fen(n); fen.add(x, val); fen.sum(x);
 */
#pragma once

struct FenwickTree {
    vector<int> tree;
    FenwickTree(int size) { tree.resize(size+1, 0); }
    int sum(int pos) {
        int ret = 0;
        for (int i=pos+1; i>0; i &= (i-1)) ret += tree[i];
        return ret;
    }
    void add(int pos, int val) {
        for (int i=pos+1; i<tree.size(); i+=(i & -i)) tree[i] += val;
    }
};
