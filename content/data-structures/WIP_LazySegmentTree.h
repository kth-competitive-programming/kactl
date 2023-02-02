/**
 * Author: A Kishore Kumar
 * Date: 2022-02-02
 * License: CC0
 * Source: https://codeforces.com/blog/entry/18051
 * Description: Supposed to be a fully modular iterative lazy segment tree. Work in progress, can't figure out why it doesn't compile.
 *      Help debug thanks.
 * Time: O(\log N).
 * Usage: we'll see
 * Status: WIP. Doesn't even compile.
 */

template<typename T, typename L> // merge, lazy
struct LazySegmentTree {
    const int n, h;
    T m_id; vector<T> tree, mset;
    L l_id; vector<L> lazy;
    T nop = numeric_limits<T>::min(); // change if T is not numeric

    function<T(T&, T&)> merge = [&](T &a, T &b){ return max(a, b); };
    function<T(T&, T&, L&, int)> mapping = [&](T &v, T &vset, L &val, int len) { 
        return (vset == nop) ? v+val : vset; };
    function<void(T&, T&, L&, L&)> compose = [&](T &cset, T &vset, L &v, L &upd){ 
        (vset == nop) ? v += upd : cset = vset; };

    void apply(int v, L &upd, T &vset, int len){
        tree[v] = mapping(tree[v], vset, upd, len);
        if(v < n) compose(mset[v], vset, upd, len);
    }
    LazySegmentTree(const vector<T> &a, T m_id, L l_id) : n(sz(a)), 
            h(32-__builtin_clz(signed(n))), m_id(m_id), l_id(l_id), 
            tree(2*n), lazy(2*n, l_id) {
        for(int i=0; i < n; i++) tree[n+i] = a[i];
        for(int i=n-1; i >= 1; i--)
            tree[i] = merge(tree[2*i], tree[2*i+1]);
    }
    void pull(int v){
        for(int p=v<<1; p >= 1; p<<=1)
            tree[p] = merge(tree[2*p], tree[2*p+1]);
    }
    void push(int v){
        for(int lvl=h,p=(v>>lvl); lvl >= 1; lvl--,p=(v>>lvl)){
            apply(2*v, lazy[v], mset[v], 1<<lvl), apply(2*v+1, lazy[v], mset[v], 1<<lvl);
            lazy[v] = l_id; mset[v] = nop;
        }
    }
    template <class B> void process(int l, int r, int msk, B op){
        int l0=l, r0=r, k=1; assert(l <= r);
        if(msk & (1 << 0)) push(l0), push(r0);
        for(l += n, r += n; l <= r; l>>=1, r>>=1, k<<=1) {
            if(l==r) B(l, k);
            if(l&1) B(l++, k);
            if(!(r&1)) B(r++, k);
        }
        if(msk & (1 << 1)) pull(l0), pull(r0);
    }
    void set(int lr, int rr, T &val){
        process(lr, rr, 0b11, [&](int v, int k){
            apply(v, l_id, val, 1<<k); });
    }
    void update(int lr, int rr, T &val){ // order of ops does not matter => msk=0b10
        process(lr, rr, 0b11, [&](int v, int k){ 
            apply(v, val, nop, 1<<k); });
    }
    T query(int lr, int rr){ // Does not work with commutative functions
        T ret = m_id; 
        process(lr, rr, 0b1, [&](int v, int k){
            ret = merge(ret, tree[v]); }); 
        return ret;
    }
};