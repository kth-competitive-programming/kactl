/**
 * Author:
 * Description: 0-indexed.
 * cf) $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Usage: Dinic g(n); g.add_edge(u, v, cap_uv, cap_vu); g.max_flow(s, t); g.clear_flow();
 */
#pragma once

struct Dinic {
    struct Edge {
        int a;
        ll flow;
        ll cap;
        int rev;
    };
    
    int n, s, t;
    vector<vector<Edge>> adj;
    vector<int> level;
    vector<int> cache;
    vector<int> q;
    Dinic(int _n) : n(_n) {
        adj.resize(n);
        level.resize(n);
        cache.resize(n);
        q.resize(n);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        int l = 0, r = 1;
        q[0] = s;
        while (l < r) {
            int here = q[l++];
            for (auto[there, flow, cap, rev]: adj[here]) {
                if (flow < cap && level[there] == -1) {
                    level[there] = level[here] + 1;
                    if (there == t) return true;
                    q[r++] = there;
                }
            }
        }
        return false;
    }

    ll dfs(int here, ll extra_capa) {
        if (here == t) return extra_capa;
        for (int& i=cache[here]; i<adj[here].size(); ++i) {
            auto[there, flow, cap, rev] = adj[here][i];
            if (flow < cap && level[there] == level[here] + 1) {
                ll f = dfs(there, min(extra_capa, cap-flow));
                if (f > 0) {
                    adj[here][i].flow += f;
                    adj[there][rev].flow -= f;
                    return f;
                }
            }
        }
        return 0;
    }

    void clear_flow() {
        for (auto& v: adj) {
            for (auto& e: v) e.flow = 0;
        }
    }

    ll max_flow(int _s, int _t) {
        s = _s, t = _t;
        ll ret = 0;
        while (bfs()) {
            fill(cache.begin(), cache.end(), 0);
            while (true) {
                ll f = dfs(s, 2e18);
                if (f == 0) break;
                ret += f;
            }
        }
        return ret;
    }

    void add_edge(int u, int v, ll uv, ll vu) {
        adj[u].push_back({ v, 0, uv, (int)adj[v].size() });
        adj[v].push_back({ u, 0, vu, (int)adj[u].size()-1 });
    }
};
