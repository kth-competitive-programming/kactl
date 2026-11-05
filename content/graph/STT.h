#pragma once

template <class DP> struct StaticTopTree {
    using G = vector<vector<int>>;
    using Data = typename DP::Data;
    int n, k;
    G g;
    vi s, q, L, R, C;
    vector<Data> dp;

    StaticTopTree(const G& h, int root = 0): n(h.size()), k(n), g(h), s(n), q(n*2, -1), L(n*2), R(n*2), C(n*2), dp(n*2){
        dfs(root, -1), path(root);
    }
    template<class F> void init(F f){
        rep(i, 0, n) dp[i] = f(i);
        rep(i, n, n*2-1) update(i);
    }
    void set(int v, const Data& d){
        for(dp[v]=d; q[v]>=0;) v = q[v], update(v);
    }
    Data get() const { return dp[k-1]; }
private:
    void dfs(int v, int p){
        g[v].erase(remove(all(g[v]), p), end(g[v])), s[v] = 1;
        for(int& u:g[v]) if(dfs(u, v), s[v] += s[u], s[u] > s[g[v][0]]) swap(u, g[v][0]);
    }
    int add(int a, int b, int c){ return q[a] = q[b] = k, L[k] = a, R[k] = b, C[k] = c, k++; }
    int build(vi& a, int c, int x, int y){
        return y-x < 2 ? a[x] : add(build(a, c, x, (x+y)/2), build(a, c, (x+y)/2, y), c);
    }
    int path(int v){
        vi a = {v};
        for(int p=v; g[p].size(); p=g[p][0]){
            vi b;
            rep(i, 1, g[p].size()) b.push_back(path(g[p][i]));
            a.push_back(b.empty() ? g[p][0] : add(g[p][0], build(b, 0, 0, b.size()), 0));
        }
        return build(a, 1, 0, a.size());
    }
    void update(int i){ dp[i] = C[i] ? DP::compress(dp[L[i]], dp[R[i]]) : DP::rake(dp[L[i]], dp[R[i]]); }
};