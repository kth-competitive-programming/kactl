/**
 * Author: koosaga
 * Description: Set MAXN. Overflow is not checked.
 * Usage: MCMF g; g.add_edge(s, e, cap, cost); g.solve(src, sink, total_size);
 * Time: 216ms on almost $K_n$ graph, for $n = 300$.
 */
#pragma once

// https://github.com/koosaga/olympiad/blob/master/Library/codes/combinatorial_optimization/flow_cost_dijkstra.cpp
const int MAXN = 800 + 5;

struct MCMF {
    struct Edge{ int pos, cap, rev; ll cost; };
    vector<Edge> gph[MAXN];
    void clear(){
        for(int i=0; i<MAXN; i++) gph[i].clear();
    }
    void add_edge(int s, int e, int x, ll c){
        gph[s].push_back({e, x, (int)gph[e].size(), c});
        gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
    }
    ll dist[MAXN];
    int pa[MAXN], pe[MAXN];
    bool inque[MAXN];
    bool spfa(int src, int sink, int n){
        memset(dist, 0x3f, sizeof(dist[0]) * n);
        memset(inque, 0, sizeof(inque[0]) * n);
        queue<int> que;
        dist[src] = 0;
        inque[src] = 1;
        que.push(src);
        bool ok = 0;
        while(!que.empty()){
            int x = que.front();
            que.pop();
            if(x == sink) ok = 1;
            inque[x] = 0;
            for(int i=0; i<gph[x].size(); i++){
                Edge e = gph[x][i];
                if(e.cap > 0 && dist[e.pos] > dist[x] + e.cost){
                    dist[e.pos] = dist[x] + e.cost;
                    pa[e.pos] = x;
                    pe[e.pos] = i;
                    if(!inque[e.pos]){
                        inque[e.pos] = 1;
                        que.push(e.pos);
                    }
                }
            }
        }
        return ok;
    }
    ll new_dist[MAXN];
    pair<bool, ll> dijkstra(int src, int sink, int n){
        priority_queue<pii, vector<pii>, greater<pii> > pq;
        memset(new_dist, 0x3f, sizeof(new_dist[0]) * n);
        new_dist[src] = 0;
        pq.emplace(0, src);
        bool isSink = 0;
        while(!pq.empty()) {
            auto tp = pq.top(); pq.pop();
            if(new_dist[tp.second] != tp.first) continue;
            int v = tp.second;
            if(v == sink) isSink = 1;
            for(int i = 0; i < gph[v].size(); i++){
                Edge e = gph[v][i];
                ll new_weight = e.cost + dist[v] - dist[e.pos];
                if(e.cap > 0 && new_dist[e.pos] > new_dist[v] + new_weight){
                    new_dist[e.pos] = new_dist[v] + new_weight;
                    pa[e.pos] = v;
                    pe[e.pos] = i;
                    pq.emplace(new_dist[e.pos], e.pos);
                }
            }
        }
        return make_pair(isSink, new_dist[sink]);
    }

    pair<ll, ll> solve(int src, int sink, int n){
        spfa(src, sink, n);
        pair<bool, ll> path;
        pair<ll,ll> ret = {0,0};
        while((path = dijkstra(src, sink, n)).first){
            for(int i = 0; i < n; i++) dist[i] += min(ll(2e15), new_dist[i]);
            ll cap = 1e18;
            for(int pos = sink; pos != src; pos = pa[pos]){
                cap = min(cap, (ll)gph[pa[pos]][pe[pos]].cap);
            }
            ret.first += cap;
            ret.second += cap * (dist[sink] - dist[src]);
            for(int pos = sink; pos != src; pos = pa[pos]){
                int rev = gph[pa[pos]][pe[pos]].rev;
                gph[pa[pos]][pe[pos]].cap -= cap;
                gph[pos][rev].cap += cap;
            }
        }
        return ret;
    }
};
