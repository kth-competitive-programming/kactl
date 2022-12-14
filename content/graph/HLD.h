/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli, Kishore Kumar
 * Date: 2022-12-14
 * License: CC0
 * Source: Folklore
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code allows for templatized types and merge functions for both
 * path and subtree queries / updates. Modify Segtree to RangeUpdate tree or Lazy
 * and update query / update functions if required. VALS\_EDGES being true means 
 * that values are stored in the edges, as opposed to the nodes. All values 
 * initialized to passed array values. Root must be 0.
 * Time: O((\log N)^2)
 * Status: Could use some more testing
 */

template <typename T, typename F, bool VAL_EDGES>
struct HLD{
    int n, timer = 0;
    vi size, top, tin, dep, par;
    Segtree<T, F> st;
    vector<T> build(vvi &adj, const vector<T> &arr){
        function<void(int)> dfs_hvy = [&](int v){
            if(sz(adj[v]) and adj[v][0] == par[v]) swap(adj[v].front(), adj[v].back());
            for(auto &to : adj[v]) if(to != par[v]) {
                par[to] = v, dep[to] = dep[v] + 1;
                dfs_hvy(to);
                size[v] += size[to];
                if(size[to] > size[adj[v][0]]) swap(to, adj[v][0]);
            }
        }; dfs_hvy(0);
        vector<T> temp(n);
        function<void(int)> dfs_hld = [&](int v){
            temp[timer] = arr[v], tin[v] = timer++;
            for(auto &to : adj[v]) if(to != par[v]) {
                top[to] = (to == adj[v][0] ? top[v] : to);
                dfs_hld(to);
            }
        }; dfs_hld(0);
        return temp;
    }
    HLD(vvi &adj, const vector<T> &arr, T id, F _m) : n(sz(adj)), size(n, 1), top(n), 
                        tin(n), dep(n), par(n, -1), st(build(adj, arr), id, _m){}
    template <class B> int process(int u, int v, B op) {
        for (; top[u] != top[v]; v = par[top[v]]) {
            if(dep[top[u]] > dep[top[v]]) swap(u, v);
            op(tin[top[v]], tin[v]);
        }
        if (dep[u] > dep[v]) swap(u, v);
        if(!VAL_EDGES or u!=v) op(tin[u] + VAL_EDGES, tin[v]);
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
    T query_subtree(int v) { // update is similar
        return (size[v] > 1 or !VAL_EDGES) ? st.query(tin[v]+VAL_EDGES, tin[v]+size[v]) : 
                                            st.identity; 
    }
}
