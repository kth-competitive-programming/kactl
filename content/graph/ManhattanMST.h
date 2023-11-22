/**
 * Author:
 * Description: Given 2d points, find MST with taxi distance.
 * Usage: 0-base index internally. taxiMST(pts); Returns mst's tree edges with (length, a, b); Note that union-find need return value.
 * Time: O(N \log N), $N = 2 \times 10^5$ in 363ms at yosupo.
 */
#pragma once

struct point { ll x, y; };

vector<tuple<ll, int, int>> taxiMST(vector<point> a){
    int n = a.size();
    vector<int> ind(n);
    iota(ind.begin(), ind.end(), 0);
    vector<tuple<ll, int, int>> edge;
    for(int k=0; k<4; k++){
        sort(ind.begin(), ind.end(), [&](int i,int j){return a[i].x-a[j].x < a[j].y-a[i].y;});
        map<ll, int> mp;
        for(auto i: ind){
            for(auto it=mp.lower_bound(-a[i].y); it!=mp.end(); it=mp.erase(it)){
                int j = it->second; point d = {a[i].x-a[j].x, a[i].y-a[j].y};
                if(d.y > d.x) break;
                edge.push_back({d.x + d.y, i, j});
            }
            mp.insert({-a[i].y, i});
        }
        for(auto &p: a) if(k & 1) p.x = -p.x; else swap(p.x, p.y);
    }
    sort(edge.begin(), edge.end());
    DisjointSet dsu(n);
    vector<tuple<ll, int, int>> res;
    for(auto [x, i, j]: edge) if(dsu.merge(i, j)) res.push_back({x, i, j});
    return res;
}
