/**
 * Author:
 * Description: Calculate Kth shortest path from s to t.
 * Usage: 0-base index. Vertex is 0 to n-1. KthShortestPath g(n); g.add_edge(s, e, cost); g.run(s, t, k);
 * Time: O(E \log V + K \log K), $V = E = K = 3 \times 10^5$ in 312ms, 144MB at yosupo.
 */
#pragma once

struct KthShortestPath {
    struct node{
        array<node*, 2> son; pair<ll, ll> val;
        node() : node(make_pair(-1e18, -1e18)) {}
        node(pair<ll, ll> val) : node(nullptr, nullptr, val) {}
        node(node *l, node *r, pair<ll, ll> val) : son({l,r}), val(val) {}
    };
    node* copy(node *x){ return x ? new node(x->son[0], x->son[1], x->val) : nullptr; }
    node* merge(node *x, node *y){ // precondition: x, y both points to new entity
        if(!x || !y) return x ? x : y;
        if(x->val > y->val) swap(x, y);
        int rd = rnd(0, 1);
        if(x->son[rd]) x->son[rd] = copy(x->son[rd]);
        x->son[rd] = merge(x->son[rd], y); return x;
    }
    
    struct edge{
        ll v, c, i; edge() = default;
        edge(ll v, ll c, ll i) : v(v), c(c), i(i) {}
    };

    vector<vector<edge>> gph, rev;
    int idx;
    vector<int> par, pae; vector<ll> dist; vector<node*> heap;
    
    KthShortestPath(int n) {
        gph = rev = vector<vector<edge>>(n);
        idx = 0;
    }
    
    void add_edge(int s, int e, ll x){
        gph[s].emplace_back(e, x, idx);
        rev[e].emplace_back(s, x, idx);
        assert(x >= 0); idx++;
    }
    
    void dijkstra(int snk){ // replace this to SPFA if edge weight is negative
        int n = gph.size();
        par = pae = vector<int>(n, -1);
        dist = vector<ll>(n, 0x3f3f3f3f3f3f3f3f);
        heap = vector<node*>(n, nullptr);
        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<>> pq;
        auto enqueue = [&](int v, ll c, int pa, int pe){
            if(dist[v] > c) dist[v] = c, par[v] = pa, pae[v] = pe, pq.emplace(c, v);
        }; enqueue(snk, 0, -1, -1); vector<int> ord;
        while(!pq.empty()){
            auto [c,v] = pq.top(); pq.pop(); if(dist[v] != c) continue;
            ord.push_back(v); for(auto e : rev[v]) enqueue(e.v, c+e.c, v, e.i);
        }
        for(auto &v : ord){
            if(par[v] != -1) heap[v] = copy(heap[par[v]]);
            for(auto &e : gph[v]){
                if(e.i == pae[v]) continue;
                ll delay = dist[e.v] + e.c - dist[v];
                if(delay < 1e18) heap[v] = merge(heap[v], new node(make_pair(delay, e.v)));
            }
        }
    }
    vector<ll> run(int s, int e, int k){
        using state = pair<ll, node*>; dijkstra(e); vector<ll> ans;
        priority_queue<state, vector<state>, greater<state>> pq;
        if(dist[s] > 1e18) return vector<ll>(k, -1);
        ans.push_back(dist[s]);
        if(heap[s]) pq.emplace(dist[s] + heap[s]->val.first, heap[s]);
        while(!pq.empty() && ans.size() < k){
            auto [cst, ptr] = pq.top(); pq.pop(); ans.push_back(cst);
            for(int j=0; j<2; j++) if(ptr->son[j])
                                       pq.emplace(cst-ptr->val.first + ptr->son[j]->val.first, ptr->son[j]);
            int v = ptr->val.second;
            if(heap[v]) pq.emplace(cst + heap[v]->val.first, heap[v]);
        }
        while(ans.size() < k) ans.push_back(-1);
        return ans;
    }
};
