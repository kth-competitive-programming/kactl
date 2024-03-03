/**
 * Author: Diego Garcia
 * Date: 2024-03-24
 * License: ???
 * Source: folklore
 * Description: Segment Tree con Lazy Propagation.
 * Usage: 0-indexed. Need to define node_t and lazy_t constructors that take
base_t, and operations to add combine.
 * Status: Tested
 */

template <class node_t, class lazy_t, class base_t>
struct SegmentTree {
    int n_;
    vector <node_t> st;
    vector <lazy_t> lzy;
    SegmentTree(vector <base_t> &a) {
        n_ = sz(a);
        st.resize(4 * n_);
        lzy.resize(4 * n_);
        build(0, 0, n_ - 1, a);
    }
    void build(int u, int l, int r, vector <base_t> &a) {
        if(l == r) { st[u] = node_t(a[l]); return; }
        int md = (l + r) / 2;
        build(2 * u + 1, l, md, a); build(2 * u + 2, md + 1, r, a);
        st[u] = st[2 * u + 1] + st[2 * u + 2];
    }
    void push(int u, int l, int r) {
        if(lzy[u].is_null()) return;
        st[u] = st[u] + lzy[u];
        if(l != r) { lzy[2 * u + 1] = lzy[2 * u + 1] + lzy[u];
                     lzy[2 * u + 2] = lzy[2 * u + 2] + lzy[u]; }
        lzy[u] = lazy_t();
    }
    void upd(int s, int e, lazy_t v) { upd(s, e, v, 0, 0, n_- 1); }
    void upd(int s, int e, lazy_t v, int u, int l, int r) {
        push(u, l, r);
        if(e < l || r < s) return;
        if(s <= l && r <= e) {
            lzy[u] = lzy[u] + v;  push(u, l, r);
            return;
        };
        int md = (l + r) / 2;
        upd(s, e, v, 2 * u + 1, l, md);
        upd(s, e, v, 2 * u + 2, md + 1, r);
        st[u] = st[2 * u + 1] + st[2 * u + 2];
    }
    node_t query(int s, int e) { return query(s, e, 0, 0, n_ - 1); }
    node_t query(int s, int e, int u, int l, int r) {
        push(u, l, r);
        if(e < l || r < s) return node_t();
        if(s <= l && r <= e) return st[u];
        int md = (l + r) / 2;
        return query(s, e, 2 * u + 1, l, md) + query(s, e, 2 * u + 2, md + 1, r);
    }
    template <class F> //first index >= i that satisfies F (monotone)
    int first_index(int i, F f) { return first_index<F>(i, 0, 0, n_ - 1, f); }
    template <class F>
    int first_index(int i, int u, int l, int r, F f) {
        push(u, l, r);
        if(r < i) return -1;
        int md = (l + r) / 2;
        if(l >= i) {
            if(!f(st[u])) return -1;
            while(l != r) {
                push(2 * u + 1, l, md); push(2 * u + 2, md + 1, r);
                if(f(st[2 * u + 1])) u = 2 * u + 1, r = md;
                else u = 2 * u + 2, l = md + 1;
                md = (l + r) / 2;
            }
            return l;
        }
        int left_attempt = first_index(i, 2 * u + 1, l, md, f);
        if(left_attempt != -1) return left_attempt;
        return first_index(i, 2 * u + 2, md + 1, r, f);
    }
    template <class F> //last index <= i that satisfies F (monotone)
    int last_index(int i, F f) { return last_index<F>(i, 0, 0, n_ - 1, f); }
    template <class F>
    int last_index(int i, int u, int l, int r, F f) {
        push(u, l, r);
        if(l > i) return -1;
        int md = (l + r) / 2;
        if(r <= i) {
            if(!f(st[u])) return -1;
            while(l != r) {
                push(2 * u + 1, l, md); push(2 * u + 2, md + 1, r);
                if(f(st[2 * u + 2])) u = 2 * u + 2, l = md + 1;
                else u = 2 * u + 1, r = md;
                md = (l + r) / 2;
            }
            return l;
        }
        int right_attempt = first_index(i, 2 * u + 2, md + 1, r, f);
        if(right_attempt != -1) return right_attempt;
        return last_index(i, 2 * u + 1, l, md, f);
    }
};
//when used on segtree these need an empty constructor, and one that takes a base_t
struct Lazy {
    Lazy() {}
    Lazy operator + (Lazy other) { };
    bool is_null() { };
};
struct Node {
    Node() {}
    Node operator + (Node other) { };
    Node operator + (Lazy other) { };
};
