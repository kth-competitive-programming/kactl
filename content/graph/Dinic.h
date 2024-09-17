/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once

struct edge{
    int from, to, cap;
};
vector<edge> edges;
vector<vector<int>> adj(605);
int level[605];
int cur[605];
int n;
int s,t;
int sendFlow(int u=s, int minFlow=INF){
    if(u==t) return minFlow;
    int totalFlow = 0;
    for(;cur[u]<adj[u].size();cur[u]++){
        edge &ff = edges[adj[u][cur[u]]];
        edge &bf = edges[adj[u][cur[u]] ^ 1ll];
        if(ff.cap <= 0) continue;
        if(level[u]+1 != level[ff.to]) continue;
        int currentFlow = sendFlow(ff.to, min(minFlow, ff.cap));
        minFlow -= currentFlow;
        ff.cap -= currentFlow;
        bf.cap += currentFlow;
        totalFlow += currentFlow;
        if(minFlow <= 0 ) break;
    }
    return totalFlow;
}
bool reachable(){
    memset(level,-1,sizeof level);
    queue<int> q;
    q.push(s);
    int cnt = 0;
    bool found =0;
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            int u = q.front(); q.pop();
            
            if(level[u]>=0) continue;
            if(u == t) found = 1;
            
            level[u] = cnt;
            
            for(int p : adj[u]) {
                edge &e = edges[p];
                if(level[e.to]>=0) continue;
                if(e.cap <= 0) continue;
                q.push(e.to); 
            }
        }
        cnt++;
        if(found) break;
    }
    return found;
}
int maxFlow(){
    int mf = 0;
    while(reachable()){
        memset(cur,0,sizeof cur);
        mf += sendFlow();
    }
    return mf;
}
void addEdge(int a, int b, int cap){
    edge tmp;
    tmp.from = a, tmp.to = b, tmp.cap = cap;
    adj[a].pb(edges.size());
    edges.pb(tmp);
    
    tmp.from = b, tmp.to = a, tmp.cap = 0;
    adj[b].pb(edges.size());
    edges.pb(tmp);
}
