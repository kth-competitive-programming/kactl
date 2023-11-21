/**
 * Author:
 * Description: Directed MST for given root node. If no MST exists, returns -1.
 * Usage: 0-base index. Vertex is 0 to n-1. typedef ll cost_t.
 * Time: O(E \log V), $V = E = 2 \times 10^5$ in 90ms at yosupo.
 */
#pragma once

struct Edge{
    int s, e; cost_t x;
    Edge() = default;
    Edge(int s, int e, cost_t x) : s(s), e(e), x(x) {}
    bool operator < (const Edge &t) const { return x < t.x; }
};
struct UnionFind{
    vector<int> P, S;
    vector<pair<int, int>> stk;
    UnionFind(int n) : P(n), S(n, 1) { iota(P.begin(), P.end(), 0); }
    int find(int v) const { return v == P[v] ? v : find(P[v]); }
    int time() const { return stk.size(); }
    void rollback(int t){
        while(stk.size() > t){
            auto [u,v] = stk.back(); stk.pop_back();
            P[u] = u; S[v] -= S[u];
        }
    }
    bool merge(int u, int v){
        u = find(u); v = find(v);
        if(u == v) return false;
        if(S[u] > S[v]) swap(u, v);
        stk.emplace_back(u, v);
        S[v] += S[u]; P[u] = v;
        return true;
    }
};
struct Node{
    Edge key;
    Node *l, *r;
    cost_t lz;
    Node() : Node(Edge()) {}
    Node(const Edge &edge) : key(edge), l(nullptr), r(nullptr), lz(0) {}
    void push(){
        key.x += lz;
        if(l) l->lz += lz;
        if(r) r->lz += lz;
        lz = 0;
    }
    Edge top(){ push(); return key; }
};
Node* merge(Node *a, Node *b){
    if(!a || !b) return a ? a : b;
    a->push(); b->push();
    if(b->key < a->key) swap(a, b);
    swap(a->l, (a->r = merge(b, a->r)));
    return a;
}
void pop(Node* &a){ a->push(); a = merge(a->l, a->r); }

// 0-based
pair<cost_t, vector<int>> DirectMST(int n, int rt, vector<Edge> &edges){
    vector<Node*> heap(n);
    UnionFind uf(n);
    for(const auto &i : edges) heap[i.e] = merge(heap[i.e], new Node(i));
    cost_t res = 0;
    vector<int> seen(n, -1), path(n), par(n);
    seen[rt] = rt;
    vector<Edge> Q(n), in(n, {-1,-1, 0}), comp;
    deque<tuple<int, int, vector<Edge>>> cyc;
    for(int s=0; s<n; s++){
        int u = s, qi = 0, w;
        while(seen[u] < 0){
            if(!heap[u]) return {-1, {}};
            Edge e = heap[u]->top();
            heap[u]->lz -= e.x; pop(heap[u]);
            Q[qi] = e; path[qi++] = u; seen[u] = s;
            res += e.x; u = uf.find(e.s);
            if(seen[u] == s){ // found cycle, contract
                Node* nd = 0;
                int end = qi, time = uf.time();
                do nd = merge(nd, heap[w = path[--qi]]); while(uf.merge(u, w));
                u = uf.find(u); heap[u] = nd; seen[u] = -1;
                cyc.emplace_front(u, time, vector<Edge>{&Q[qi], &Q[end]});
            }
        }
        for(int i=0; i<qi; i++) in[uf.find(Q[i].e)] = Q[i];
    }
    for(auto& [u,t,comp] : cyc){
        uf.rollback(t);
        Edge inEdge = in[u];
        for (auto& e : comp) in[uf.find(e.e)] = e;
        in[uf.find(inEdge.e)] = inEdge;
    }
    for(int i=0; i<n; i++) par[i] = in[i].s;
    return {res, par};
}
