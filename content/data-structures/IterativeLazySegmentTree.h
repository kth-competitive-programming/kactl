/**
 * Author: A Kishore Kumar
 * Date: 2022-02-02
 * License: CC0
 * Source: https://codeforces.com/blog/entry/18051
 * ExtDesc: An iterative lazy segment tree implementation. O(\log N).
 * Description: If harsh TL manually inline merge, mapping, compose and process. Segtree of vector faster than vector of segtree.
 * Status: Needs testing.
 */

template<typename T, typename L>
struct LazySegmentTree {
    int n, h;
    T m_id; vector<T> tree;
    L l_id; vector<L> lazy;

    T merge(T a, T b) { return max(a, b); }
    T mapping(T v, L val, int len) { return v+val; }
    void compose(L &cl, L &ul, int len){ cl += ul; }

    void apply(int v, L upd, int len){
        tree[v] = mapping(tree[v], upd, len);
        if(v < n) compose(lazy[v], upd, len);
    }
    LazySegmentTree(const vector<T> &a, T m_id, L l_id) : n(sz(a)), 
            h(32-__builtin_clz(signed(n))), m_id(m_id), tree(2*n),
            l_id(l_id), lazy(n, l_id){
        for(int i=0; i < n; i++) tree[n+i] = a[i];
        for(int i=n-1; i >= 1; i--)
            tree[i] = merge(tree[2*i], tree[2*i+1]);
    }
    void pull(int v){
        for(int p=v>>1, k=2; p >= 1; p>>=1, k<<=1)
            tree[p] = mapping(merge(tree[2*p], tree[2*p+1]), lazy[p], k);
    }
    void push(int v){
        for(int lvl=h,p=(v>>lvl); lvl >= 1; lvl--,p=(v>>lvl)){
            int k = 1 << (lvl-1);
            apply(2*p, lazy[p], k), apply(2*p+1, lazy[p], k);
            lazy[p] = l_id;
        }
    }
    template <class B> void process(int l, int r, int msk, B op){
        int l0=l+n, r0=r+n, k=1; assert(l <= r);
        if(msk & (1 << 0)) push(l0), push(r0);
        for(l += n, r += n; l <= r; l>>=1, r>>=1, k<<=1) {
            if(l == r) { op(l, k); break; }
            if(l&1) op(l++, k);
            if(!(r&1)) op(r--, k);
        }
        if(msk & (1 << 1)) pull(l0), pull(r0);
    }
    void update(int lr, int rr, L val){ // Commutatvie upd => msk=0b10
        process(lr, rr, 0b11, [&](int v, int k){ apply(v, val, k); });
    }
    T query(int lr, int rr){ // Does not work with commutative functions
        T ret = m_id; 
        process(lr, rr, 0b1, [&](int v, int k){ ret = merge(ret, tree[v]); }); 
        return ret;
    }
};