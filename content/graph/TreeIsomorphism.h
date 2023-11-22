/**
 * Author:
 * Description: Calculate hash of given tree.
 * Usage: 1-base index. t.init(n); t.add_edge(a, b); (size, hash) = t.build(void); // size may contain dummy centroid.
 * Time: O(N \log N), $N = 30$ and $\sum N \leq 10^6$ in 256ms.
 */
#pragma once

const int MAX_N = 33;
ull A[MAX_N], B[MAX_N];

struct Tree {
    int n;
    vector<int> adj[MAX_N];
    int sz[MAX_N];
    vector<int> cent; // sz(cent) <= 2
    Tree() {}

    void init(int n) {
        this->n = n;
        for (int i=0; i<n+2; ++i) adj[i].clear();
        fill(sz, sz+n+2, 0);
        cent.clear();
    }
    
    void add_edge(int s, int e) {
        adj[s].push_back(e);
        adj[e].push_back(s);
    }
    
    int get_cent(int v, int b = -1) {
        sz[v] = 1;
        for (auto i: adj[v]) {
            if (i != b) {
                int now = get_cent(i, v);
                if (now <= n/2) sz[v] += now;
                else break;
            }
        }
        if (n - sz[v] <= n/2) cent.push_back(v);
        return sz[v];
    }
    
    int init() {
        get_cent(1);
        if (cent.size() == 1) return cent[0];
        int u = cent[0], v = cent[1], add = ++n;
        adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
        adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
        adj[add].push_back(u); adj[u].push_back(add);
        adj[add].push_back(v); adj[v].push_back(add);
        return add;
    }

    pair<int, ull> build(int v, int p = -1, int d = 1) {
        vector<pair<int, ull>> ch;
        for (auto i: adj[v]) {
            if (i != p) ch.push_back(build(i, v, d+1));
        }
        if (ch.empty()) return { 1, d };
        
        sort(ch.begin(), ch.end());
        ull ret = d;
        int tmp = 1;
        for (int j=0; j<ch.size(); ++j) {
            ret += A[d] ^ B[j] ^ ch[j].second;
            tmp += ch[j].first;
        }
        return { tmp, ret };
    }
    
    pair<int, ull> build() {
        return build(init());
    }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ull> urnd;

void solve() {
    for (int i=0; i<MAX_N; ++i) A[i] = urnd(rng), B[i] = urnd(rng);
}
