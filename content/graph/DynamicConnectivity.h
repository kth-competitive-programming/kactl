/**
 * Author: Joshua Chen
 * Date: 2023-11-23
 * License: CC0
 * Source: https://github.com/Joshc88/CPTemplates/blob/main/Graph/dynamicconnectivity.h
 * Description: Performs dynamic connectivity
 * Time: O(QlogQlogM)
 * Status: Tested
 */
#pragma once

struct dsu {
    int n;
    vector<int> parent, sz, big;
    vector<pair<pii, pii>> ops; // {{node1, node2}, {became_connected, previous_answer}}

    dsu() {}

    dsu(int N) {
        n = N;
        parent = vector<int>(n+1);
        iota(parent.begin(), parent.end(), 0);
        big = parent;
        sz = vector<int>(n+1, 1);
    }
    
    int root(int x) {
        while (x != parent[x]) x = parent[x];
        return x;
    }
    
    void join(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) {
            ops.push_back(mp(mp(x, y), mp(0, big[y])));
            return;
        }
        if (sz[x] > sz[y]) swap(x, y);
        ops.push_back(mp(mp(x, y), mp(1, big[y])));
        parent[x] = y;
        sz[y] += sz[x];
        big[y] = max(big[y], big[x]);
    }
    
    void undo() {
        auto p = ops.back();
        ops.pop_back();
        if (!p.s.f) return;
        parent[p.f.f] = p.f.f;
        sz[p.f.s] -= sz[p.f.f];
        big[p.f.s] = p.s.s;
    }  
};

struct dynamicDSU {
    int n, timer = 1, queryindex = 0;
    dsu d;
    vector<int> ans;
    vector<vector<pii>> queries = {{}, {}};
    vector<vector<pii>> seg;
    map<pii, vector<int>> times;
 
    void update(int v, int tl, int tr, int l, int r, pii x) {
        if (l > r) return;
        if (l == tl && r == tr) seg[v].push_back(x);
        else {
            int tm = (tl+tr) >> 1;
            update(v+1, tl, tm, l, min(r, tm), x);
            update(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r, x);
        }
    }
    
    void dfs(int v, int tl, int tr) {
        for (pii p : seg[v]) d.join(p.f, p.s);
        if (tl == tr) {
            for (pii i : queries[tl]) ans[i.f] = d.big[d.root(i.s)];
        }
        else {
            int tm = (tl+tr) >> 1;
            dfs(v+1, tl, tm);
            dfs(v+2*(tm-tl+1), tm+1, tr);
        }
        for (pii p : seg[v]) d.undo();
    }

    dynamicDSU() {}

    dynamicDSU(int N) {
        n = N;
        d = dsu(n);
    }

    void update(int x, int y) {
        // Add or disconnect the edge between x and y
        if (x > y) swap(x, y);
        times[mp(x, y)].push_back(++timer);
        queries.push_back({});
    }

    void query(int x) {
        // Add a query
        queries[timer].push_back(mp(queryindex++, x));
    }

    vector<int> solve() {
        seg.resize(2*timer+5);
        ans.resize(queryindex);
        for (auto p : times) {
            if (p.s.size()&1) p.s.push_back(timer+1);
            for (int j=0; j<p.s.size(); j+=2) update(1, 1, timer, p.s[j], p.s[j+1]-1, p.f);
        }
        dfs(1, 1, timer);
        return ans;
    }
};