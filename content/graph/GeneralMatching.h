/**
 * Author:
 * Description: Matching for general graphs.
 * Usage: 1-base index. match[] has real matching (maybe). GeneralMatching g(n); g.add_edge(a, b); int ret = g.run(void);
 * Time: O(N^3), $N = 500$ in 20ms.
 */
#pragma once

const int MAX_N = 500 + 1;

struct GeneralMatching {
    int n, cnt;
    int match[MAX_N], par[MAX_N], chk[MAX_N], prv[MAX_N], vis[MAX_N];
    vector<int> g[MAX_N];
    GeneralMatching(int n): n(n) {
        // init
        cnt = 0;
        for (int i=0; i<=n; ++i) g[i].clear();
        memset(match, 0, sizeof match);
        memset(vis, 0, sizeof vis);
        memset(prv, 0, sizeof prv);
    }

    int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }

    int lca(int u, int v) { 
        for (cnt++; vis[u] != cnt; swap(u, v)) {
            if (u) vis[u] = cnt, u = find(prv[match[u]]);
        }
        return u;
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void blossom(int u, int v, int rt, queue<int> &q) {
        for (; find(u) != rt; u = prv[v]) {
            prv[u] = v; 
            par[u] = par[v = match[u]] = rt; 
            if (chk[v] & 1) q.push(v), chk[v] = 2;
        }
    }

    bool augment(int u) {
        iota(par, par + MAX_N, 0); 
        memset(chk, 0, sizeof chk); 
        queue<int> q; 
        q.push(u); 
        chk[u] = 2;
    
        while (!q.empty()) {
            u = q.front(); 
            q.pop();
            for (auto v : g[u]) {
                if (chk[v] == 0) {
                    prv[v] = u; 
                    chk[v] = 1; 
                    q.push(match[v]); 
                    chk[match[v]] = 2;
                    if (!match[v]) { 
                        for (; u; v = u) {
                            u = match[prv[v]]; 
                            match[match[v] = prv[v]] = v; 
                        }
                        return true;
                    }
                } else if (chk[v] == 2) {
                    int l = lca(u, v); 
                    blossom(u, v, l, q);
                    blossom(v, u, l, q); 
                }
            }
        }
        return false;
    }

    int run() {
        int ret = 0;
        vector<int> tmp(n-1); // not necessary, just for constant optimization
        iota(tmp.begin(), tmp.end(), 0);
        shuffle(tmp.begin(), tmp.end(), mt19937(0x1557));
        for (auto x: tmp) {
            if (!match[x]) {
                for (auto y: g[x]) {
                    if (!match[y]) {
                        match[x] = y;
                        match[y] = x;
                        ret++;
                        break;
                    }
                }
            }
        }
        for (int i=1; i<=n; i++) { 
            if (!match[i]) ret += augment(i);
        }
        return ret;
    }
};
