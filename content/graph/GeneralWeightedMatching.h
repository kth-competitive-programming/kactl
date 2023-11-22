/**
 * Author:
 * Description: Given a weighted undirected graph, return maximum matching.
 * Usage: 1-base index. init(n); add_edge(a, b, w); (tot_weight, n_matches) = _solve(void); Note that get_lca function have a static variable.
 * Time: O(N^3), $N = 500$ in 317ms at yosupo.
 */
#pragma once

static const int INF = INT_MAX;
static const int N = 500 + 1;

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int ui, int vi, int wi) : u(ui), v(vi), w(wi) {}
};

int n, n_x;
Edge g[N * 2][N * 2];
int lab[N * 2];
int match[N * 2], slack[N * 2], st[N * 2], pa[N * 2];
int flo_from[N * 2][N + 1], s[N * 2], vis[N * 2];
vector<int> flo[N * 2];
queue<int> q;

int e_delta(const Edge &e) {
    return lab[e.u] + lab[e.v] - g[e.u][e.v].w * 2;
}

void update_slack(int u, int x) {
    if (!slack[x] || e_delta(g[u][x]) < e_delta(g[slack[x]][x])) slack[x] = u;
}

void set_slack(int x) {
    slack[x] = 0;
    for (int u = 1; u <= n; ++u) {
        if (g[u][x].w > 0 && st[u] != x && s[st[u]] == 0) update_slack(u, x);
    }
}

void q_push(int x) {
    if (x <= n) {
        q.push(x);
    } else {
        for (size_t i = 0; i < flo[x].size(); i++) q_push(flo[x][i]);
    }
}

void set_st(int x, int b) {
    st[x] = b;
    if (x > n) {
        for (size_t i = 0; i < flo[x].size(); ++i) set_st(flo[x][i], b);
    }
}

int get_pr(int b, int xr) {
    int pr = find(flo[b].begin(), flo[b].end(), xr) - flo[b].begin();
    if (pr % 2 == 1) {
        reverse(flo[b].begin() + 1, flo[b].end());
        return (int)flo[b].size() - pr;
    } else {
        return pr;
    }
}

void set_match(int u, int v) {
    match[u] = g[u][v].v;
    if (u <= n) return;
    Edge e = g[u][v];
    int xr = flo_from[u][e.u], pr = get_pr(u, xr);
    for (int i = 0; i < pr; ++i) set_match(flo[u][i], flo[u][i ^ 1]);
    set_match(xr, v);
    rotate(flo[u].begin(), flo[u].begin() + pr, flo[u].end());
}

void augment(int u, int v) {
    for (;;) {
        int xnv = st[match[u]];
        set_match(u, v);
        if (!xnv) return;
        set_match(xnv, st[pa[xnv]]);
        u = st[pa[xnv]], v = xnv;
    }
}

int get_lca(int u, int v) {
    static int t = 0;
    for (++t; u || v; swap(u, v)) {
        if (u == 0) continue;
        if (vis[u] == t) return u;
        vis[u] = t;
        u = st[match[u]];
        if (u) u = st[pa[u]];
    }
    return 0;
}

void add_blossom(int u, int lca, int v) {
    int b = n + 1;
    while (b <= n_x && st[b]) ++b;
    if (b > n_x) ++n_x;
    lab[b] = 0, s[b] = 0;
    match[b] = match[lca];
    flo[b].clear();
    flo[b].push_back(lca);
    for (int x = u, y; x != lca; x = st[pa[y]]) {
        flo[b].push_back(x), flo[b].push_back(y = st[match[x]]), q_push(y);
    }
    reverse(flo[b].begin() + 1, flo[b].end());
    for (int x = v, y; x != lca; x = st[pa[y]]) {
        flo[b].push_back(x), flo[b].push_back(y = st[match[x]]), q_push(y);
    }
    set_st(b, b);
    for (int x = 1; x <= n_x; ++x) g[b][x].w = g[x][b].w = 0;
    for (int x = 1; x <= n; ++x) flo_from[b][x] = 0;
    for (size_t i = 0; i < flo[b].size(); ++i) {
        int xs = flo[b][i];
        for (int x = 1; x <= n_x; ++x)
            if (g[b][x].w == 0 || e_delta(g[xs][x]) < e_delta(g[b][x])) {
                g[b][x] = g[xs][x], g[x][b] = g[x][xs];
            }
        for (int x = 1; x <= n; ++x)
            if (flo_from[xs][x]) flo_from[b][x] = xs;
    }
    set_slack(b);
}

void expand_blossom(int b) {
    for (size_t i = 0; i < flo[b].size(); ++i) set_st(flo[b][i], flo[b][i]);
    int xr = flo_from[b][g[b][pa[b]].u], pr = get_pr(b, xr);
    for (int i = 0; i < pr; i += 2) {
        int xs = flo[b][i], xns = flo[b][i + 1];
        pa[xs] = g[xns][xs].u;
        s[xs] = 1, s[xns] = 0;
        slack[xs] = 0, set_slack(xns);
        q_push(xns);
    }
    s[xr] = 1, pa[xr] = pa[b];
    for (size_t i = pr + 1; i < flo[b].size(); ++i) {
        int xs = flo[b][i];
        s[xs] = -1, set_slack(xs);
    }
    st[b] = 0;
}

bool on_found_edge(const Edge &e) {
    int u = st[e.u], v = st[e.v];
    if (s[v] == -1) {
        pa[v] = e.u, s[v] = 1;
        int nu = st[match[v]];
        slack[v] = slack[nu] = 0;
        s[nu] = 0, q_push(nu);
    } else if (s[v] == 0) {
        int lca = get_lca(u, v);
        if (!lca) return augment(u, v), augment(v, u), true;
        else add_blossom(u, lca, v);
    }
    return false;
}

bool matching() {
    memset(s + 1, -1, sizeof(int) * n_x);
    memset(slack + 1, 0, sizeof(int) * n_x);
    q = queue<int>();
    for (int x = 1; x <= n_x; ++x)
        if (st[x] == x && !match[x]) pa[x] = 0, s[x] = 0, q_push(x);
    if (q.empty()) return false;
    for (;;) {
        while (q.size()) {
            int u = q.front(); q.pop();
            if (s[st[u]] == 1) continue;
            for (int v = 1; v <= n; ++v)
                if (g[u][v].w > 0 && st[u] != st[v]) {
                    if (e_delta(g[u][v]) == 0) {
                        if (on_found_edge(g[u][v])) return true;
                    } else update_slack(u, st[v]);
                }
        }
        int d = INF;
        for (int b = n + 1; b <= n_x; ++b)
            if (st[b] == b && s[b] == 1) d = min(d, lab[b] / 2);
        for (int x = 1; x <= n_x; ++x)
            if (st[x] == x && slack[x]) {
                if (s[x] == -1) d = min(d, e_delta(g[slack[x]][x]));
                else if (s[x] == 0) d = min(d, e_delta(g[slack[x]][x]) / 2);
            }
        for (int u = 1; u <= n; ++u) {
            if (s[st[u]] == 0) {
                if (lab[u] <= d) return 0;
                lab[u] -= d;
            } else if (s[st[u]] == 1) lab[u] += d;
        }
        for (int b = n + 1; b <= n_x; ++b)
            if (st[b] == b) {
                if (s[st[b]] == 0) lab[b] += d * 2;
                else if (s[st[b]] == 1) lab[b] -= d * 2;
            }
        q = queue<int>();
        for (int x = 1; x <= n_x; ++x)
            if (st[x] == x && slack[x] && st[slack[x]] != x && e_delta(g[slack[x]][x]) == 0)
                if (on_found_edge(g[slack[x]][x])) return true;
        for (int b = n + 1; b <= n_x; ++b)
            if (st[b] == b && s[b] == 1 && lab[b] == 0) expand_blossom(b);
    }
    return false;
}

pair<long long, int> _solve() {
    memset(match + 1, 0, sizeof(int) * n);
    n_x = n;
    int n_matches = 0;
    long long tot_weight = 0;
    for (int u = 0; u <= n; ++u) st[u] = u, flo[u].clear();
    int w_max = 0;
    for (int u = 1; u <= n; ++u)
        for (int v = 1; v <= n; ++v) {
            flo_from[u][v] = (u == v ? u : 0);
            w_max = max(w_max, g[u][v].w);
        }
    for (int u = 1; u <= n; ++u) lab[u] = w_max;
    while (matching()) ++n_matches;
    for (int u = 1; u <= n; ++u)
        if (match[u] && match[u] < u) tot_weight += g[u][match[u]].w;
    return make_pair(tot_weight, n_matches);
}

void add_edge(int ui, int vi, int wi) {
    g[ui][vi].w = g[vi][ui].w = wi;
}

void init(int _n) {
    n = _n;
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) g[u][v] = Edge(u, v, 0);
    }
}
