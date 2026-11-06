/**
 * Author: Julio
 * Source: jiangly + me 
 * Description: Offline incremental SCCs(d&c over timeline)
 * Time: O(n log n)
 * Status: tested
 */

const int N = 400000 + 10; 
pii edges[N]; 
ll ans[N]; 
vi adj[N]; 
int low[N], comp[N], vis[N], num[N]; 
vi st; 
int timer = 0, nc = 0; 
void dfs(int u) { 
    num[u] = low[u] = timer++; 
    st.push_back(u) ; 
    for(int v : adj[u]) { 
        if(num[v] == -1) { 
            dfs(v); 
            low[u] = min(low[u], low[v]); 
        }else if(comp[v] == -1) low[u] = min(low[u], num[v]); 
    }
    if(num[u] == low[u]) { 
        int y; 
        do { 
            y = st.back(); 
            comp[y] = nc; 
            st.pop_back(); 
        }while(y != u); 
        nc++; 
    }
}   
 
void solve(int l, int r, vi edgesIdx, vi vertexIdx) { 
    timer = nc = 0 ; 
    for(auto i : vertexIdx) { 
        adj[i].clear(); 
        low[i] = comp[i] = num[i] = -1; 
        vis[i] = 0; 
    }    
    for(int i : edgesIdx) { 
        if(i >= r) continue; 
        auto [x, y] = edges[i]; 
        x = dsu.get(x); 
        y = dsu.get(y); 
        if(x == y) continue; 
        adj[x].push_back(y); 
    }
    for(auto i : vertexIdx) { 
        if(num[i] == -1) dfs(i); 
    }
    vi nE, nV; 
    for(int i : edgesIdx) { 
        if(i >= r) continue;
        auto [x, y] = edges[i]; 
        x = dsu.get(x); 
        y = dsu.get(y); 
        if(x == y) continue; 
        if(comp[x] == comp[y]) {
            if(!vis[x]) { 
                vis[x] = 1; 
                nV.push_back(x); 
            } 
            if(!vis[y]) { 
                vis[y] = 1; 
                nV.push_back(y); 
            }
            nE.push_back(i); 
        }
    }
    if(r - l == 1) { 
        for(auto i : nE) { 
            auto [x, y] = edges[i]; 
            dsu.unite(x, y); 
        }
        ans[l] = total ; 
        return; 
    }
 
    int m = (l + r) / 2; 
    solve(l, m, nE, nV); 
    solve(m, r, nE, nV); 
}   
 