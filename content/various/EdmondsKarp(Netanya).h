/**
 * Author: Netanya Robinson
 * Date: 2022-10-30
 * License: CC0
 * Source: own work
 * Description:
 * Edmonds-Karp Max Flow
 * Usage:
	int res = maxFlow(source, sink);
 * Time: Refer to other MaxFlow implementation
 * Status: tested
 */

#pragma once

ll N, M, cap[MAXN][MAXN], res[MAXN][MAXN];
vector<ll> adj[MAXN];
 
ll bfs(ll s, ll t, vector<ll>& p){
    fill(p.begin(), p.end(), -1);

    // make source unreachable
    p[s] = -2;
 
    queue<pi> q;
    q.push({s, INF});
 
    while(!q.empty()){
        ll n, flow;
        tie(n, flow) = q.front(); q.pop();
        for(ll e : adj[n]){
            if(p[e] == -1 && res[n][e]){
                p[e] = n;
                ll nf = min(flow, res[n][e]);
                if(e == t) return nf;
                q.push({e, nf});                
            }
        }
    }
 
    return 0;
}
 
ll maxFlow(ll s, ll t){
    vector<ll> p(N+1);
    ll flow = 0;
    
    while(1){
        ll nf = bfs(s, t, p);
        if(!nf) break;
        flow += nf;
 
        ll curr = t;
        while(curr != s){
            ll pred = p[curr];
            res[pred][curr] -= nf;
            res[curr][pred] += nf;
            curr = pred;
        }
    }
    return flow;
}