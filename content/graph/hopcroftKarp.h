/**
 * Author:
 * Description: It contains several application of bipartite matching. 
 * Usage: Both left and right side of node number starts with 0. HopcraftKarp(n, m); g.add_edge(s, e);
 * Time: O(E \sqrt{V}), min path cover $V = 10^4, E = 10^5$ in 20ms.
 */
#pragma once

struct HopcroftKarp{
    int n, m;
    vector<vector<int>> g;
    vector<int> dst, le, ri;
    vector<char> visit, track;
    HopcroftKarp(int n, int m) : n(n), m(m), g(n), dst(n), le(n, -1), ri(m, -1), visit(n), track(n+m) {}
    
    void add_edge(int s, int e){ g[s].push_back(e); }
    bool bfs(){
        bool res = false; queue<int> que;
        fill(dst.begin(), dst.end(), 0);
        for(int i=0; i<n; i++)if(le[i] == -1)que.push(i),dst[i]=1;
        while(!que.empty()){
            int v = que.front(); que.pop();
            for(auto i : g[v]){
                if(ri[i] == -1) res = true;
                else if(!dst[ri[i]])dst[ri[i]]=dst[v]+1,que.push(ri[i]);
            }
        }
        return res;
    }
    bool dfs(int v){
        if(visit[v]) return false; visit[v] = 1;
        for(auto i : g[v]){
            if(ri[i] == -1 || !visit[ri[i]] && dst[ri[i]] == dst[v] + 1 && dfs(ri[i])){
                le[v] = i; ri[i] = v; return true;
            }
        }
        return false;
    }
    int maximum_matching(){
        int res = 0; fill(le.begin(), le.end(), -1); fill(ri.begin(), ri.end(), -1);
        while(bfs()){
            fill(visit.begin(), visit.end(), 0);
            for(int i=0; i<n; i++) if(le[i] == -1) res += dfs(i);
        }
        return res;
    }
    vector<pair<int,int>> maximum_matching_edges(){
        int matching = maximum_matching();
        vector<pair<int,int>> edges; edges.reserve(matching);
        for(int i=0; i<n; i++) if(le[i] != -1) edges.emplace_back(i, le[i]);
        return edges;
    }
    void dfs_track(int v){
        if(track[v]) return; track[v] = 1;
        for(auto i : g[v]) track[n+i] = 1, dfs_track(ri[i]);
    }
    tuple<vector<int>, vector<int>, int> minimum_vertex_cover(){
        int matching = maximum_matching(); vector<int> lv, rv;
        fill(track.begin(), track.end(), 0);
        for(int i=0; i<n; i++) if(le[i] == -1) dfs_track(i);
        for(int i=0; i<n; i++) if(!track[i]) lv.push_back(i);
        for(int i=0; i<m; i++) if(track[n+i]) rv.push_back(i);
        return {lv, rv, lv.size() + rv.size()}; // s(lv)+s(rv)=mat
    }
    tuple<vector<int>, vector<int>, int> maximum_independent_set(){
        auto [a,b,matching] = minimum_vertex_cover();
        vector<int> lv, rv; lv.reserve(n-a.size()); rv.reserve(m-b.size());
        for(int i=0, j=0; i<n; i++){
            while(j < a.size() && a[j] < i) j++;
            if(j == a.size() || a[j] != i) lv.push_back(i);
        }
        for(int i=0, j=0; i<m; i++){
            while(j < b.size() && b[j] < i) j++;
            if(j == b.size() || b[j] != i) rv.push_back(i);
        } // s(lv)+s(rv)=n+m-mat
        return {lv, rv, lv.size() + rv.size()};
    }
    vector<vector<int>> minimum_path_cover(){ // n == m
        int matching = maximum_matching();
        vector<vector<int>> res; res.reserve(n - matching);
        fill(track.begin(), track.end(), 0);
        auto get_path = [&](int v) -> vector<int> {
            vector<int> path{v}; // ri[v] == -1
            while(le[v] != -1) path.push_back(v=le[v]);
            return path;
        };
        for(int i=0; i<n; i++) if(!track[n+i] && ri[i] == -1) res.push_back(get_path(i));
        return res; // sz(res) = n-mat
    }
    vector<int> maximum_anti_chain(){ // n = m
        auto [a,b,matching] = minimum_vertex_cover();
        vector<int> res; res.reserve(n - a.size() - b.size());
        for(int i=0, j=0, k=0; i<n; i++){
            while(j < a.size() && a[j] < i) j++;
            while(k < b.size() && b[k] < i) k++;
            if((j == a.size() || a[j] != i) && (k == b.size() || b[k] != i)) res.push_back(i);
        }
        return res; // sz(res) = n-mat
    }
};
