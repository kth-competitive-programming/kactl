/**
 * Note: Recheck the indexing for VAL_ON_EDGES = true. Haven't verified beyond testing on a CF problem.
 * NOT STRESS-TESTED
*/

template <typename T, typename F, bool VAL_ON_EDGES>
struct HLD{
    int n, timer = 0;
    vi size, top, tin, dep, par;
    Segtree<T, F> st;
    HLD(vvi &adj, const vector<T> &arr, T id, F _m) : n(sz(adj)), size(n, 1), top(n), tin(n), dep(n), par(n, -1){
        function<void(int)> dfs_hvy = [&](int v){
            if(adj[v][0] == par[v]) swap(adj[v].front(), adj[v].back());
            for(auto &to : adj[v]) if(to != par[v]) {
                par[to] = v, dep[to] = dep[v] + 1;
                dfs_hvy(to);
                size[v] += size[to];
                if(size[to] > size[adj[v][0]]) swap(to, adj[v][0]);
            }
        }; dfs_hvy(0);
        vector<T> temp; temp.reserve(n);
        function<void(int)> dfs_hld = [&](int v){
            tin[v] = timer++; temp.pb(arr[v]);
            for(auto &to : adj[v]) if(to != par[v]) {
                top[to] = (to == adj[v][0] ? top[v] : to);
                dfs_hld(to);
            }
        }; dfs_hld(0);
        st = Segtree<T, decltype(_m)>(temp, id, _m);
    }
    template <class B> int process(int u, int v, B op) {
        for (; top[u] != top[v]; v = par[top[v]]) {
            if(dep[top[u]] > dep[top[v]]) swap(u, v);
            op(tin[top[v]], tin[v]);
        }
        if (dep[u] > dep[v]) swap(u, v);
        if(!VAL_ON_EDGES or u!=v) op(tin[u] + VAL_ON_EDGES, tin[v]);
        return u;
    }
    int lca(int u, int v) { return process(u, v, [&](int,int){}); }
    T query(int u, int v){
        T ans = st.identity;
        process(u, v, [&](int l, int r){
            ans = st.merge(ans, st.query(l, r));
        });
        return ans;
    }
    void update(int v, T val){
        st.update(tin[v], val);
    }
};