/**
 * Author:
 * Description: Given a simple, undirected graph with max degree $D$, computes a
 * $(D + 1)$-coloring of the edges such that no neighboring edges share a color.
 * Usage: 1-base index. Vizing g; g.clear(V); g.solve(edges, V); answer saved in G.
 * Time: O(VE), $\sum VE = 1.1 \times 10^6$ in 24ms.
 */
#pragma once

const int MAX_N = 444 + 1;
struct Vizing { // returns edge coloring in adjacent matrix G. 1 - based
    int C[MAX_N][MAX_N], G[MAX_N][MAX_N];
    
    void clear(int n){
        for (int i=0; i<=n; i++){
            for (int j=0; j<=n; j++) C[i][j] = G[i][j] = 0;
        }
    }
    
    void solve(vector<pii> &E, int n){
        int X[MAX_N] = {}, a;
        
        auto update = [&](int u) {
            for (X[u] = 1; C[u][X[u]]; X[u]++);
        };
        
        auto color = [&](int u, int v, int c) {
            int p = G[u][v];
            G[u][v] = G[v][u] = c;
            C[u][c] = v;
            C[v][c] = u;
            C[u][p] = C[v][p] = 0;
            if (p) X[u] = X[v] = p;
            else update(u), update(v);
            return p;
        };
        
        auto flip = [&](int u, int c1, int c2){
            int p = C[u][c1]; swap(C[u][c1], C[u][c2]);
            if (p) G[u][p] = G[p][u] = c2;
            if (!C[u][c1]) X[u] = c1;
            if (!C[u][c2]) X[u] = c2;
            return p;
        };
        
        for (int i=1; i <= n; i++) X[i] = 1;
        for (int t=0; t<E.size(); ++t) {
            auto[u, v0] = E[t];
            int v = v0, c0 = X[u], c=c0, d;
            vector<pii> L;
            int vst[MAX_N] = {};
            while (!G[u][v0]) {
                L.emplace_back(v, d = X[v]);
                if(!C[v][c]) for(a = (int)L.size()-1; a >= 0; a--) c = color(u, L[a].first, c);
                else if (!C[u][d]) for(a=(int)L.size()-1;a>=0;a--) color(u,L[a].first,L[a].second);
                else if (vst[d]) break;
                else vst[d] = 1, v = C[u][d];
            }
            
            if(!G[u][v0]) {
                for (; v; v = flip(v, c, d), swap(c, d));
                if(C[u][c0]){
                    for(a = (int)L.size()-2; a >= 0 && L[a].second != c; a--);
                    for(; a >= 0; a--) color(u, L[a].first, L[a].second);
                } else t--;
            }
        }
    }
};
