/**
 * Author: sharaelong
 * Description: 0-index, [l, r] interval
 * Usage: SegmentTree seg(n); seg.query(l, r); seg.update(l, r, val);
 */
#pragma once

struct SegmentTree {
    int n, h;
    vector<int> arr;
    vector<int> lazy;
    SegmentTree(int _n) : n(_n) {
        h = Log2(n);
        n = 1 << h;
        arr.resize(2*n, 0);
        lazy.resize(2*n, 0);
    }

    void update(int l, int r, int c) {
        l += n, r += n;
        for (int i=h; i>=1; --i) {
            if (l >> i << i != l) push(l >> i);
            if ((r+1) >> i << i != (r+1)) push(r >> i);
        }
        for (int L=l, R=r; L<=R; L/=2, R/=2) {
            if (L & 1) apply(L++, c);
            if (~R & 1) apply(R--, c);
        }
        for (int i=1; i<=h; ++i) {
            if (l >> i << i != l) pull(l >> i);
            if ((r+1) >> i << i != (r+1)) pull(r >> i);
        }
    }

    int query(int l, int r) {
        l += n, r += n;
        for (int i=h; i>=1; --i) {
            if (l >> i << i != l) push(l >> i);
            if ((r+1) >> i << i != (r+1)) push(r >> i);
        }
        int ret = 0;
        for (; l <= r; l/=2, r/=2) {
            if (l & 1) ret = max(ret, arr[l++]);
            if (~r & 1) ret = max(ret, arr[r--]);
        }
        return ret;
    }

    void push(int x) {
        if (lazy[x] != 0) {
            apply(2*x, lazy[x]);
            apply(2*x+1, lazy[x]);
            lazy[x] = 0;
        }
    }

    void apply(int x, int c) {
        arr[x] = max(arr[x], c);
        if (x < n) lazy[x] = c;
    }

    void pull(int x) {
        arr[x] = max(arr[2*x], arr[2*x+1]);
    }

    static int Log2(int x){
        int ret = 0;
        while (x > (1 << ret)) ret++;
        return ret;
    }
};
