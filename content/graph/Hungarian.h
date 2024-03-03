/**
 * Author: ???
 * Date: 2015-02-24
 * License: CC0
 * Source: e-maxx
 * Description: Maximum matching minimum cost
 * Usage: 1-indexed. For non complete bipartite graph add edges (u, v) with cost inf. For Maximum matching maximum cost multiply the weights by -1. Matching $(u, v)$ is stored in M. Make sure $n=$ rows $\leq$ columns $=m$.
 * Time: $O(n^3)$ --O(n^2 m) for non-square matrix--
 * Status: Tested
 */
const ll inf = 1e18;

struct Hungarian{
public:
    int n,m;
    vvll w;
    ll min_cost;
    vp M;

    Hungarian(vvll &w){
        this->w = w;
        n = w.size()-1;
        m = w[0].size()-1;
        run();
        return;
    }

private:
    void run(){
        vll u(n+1), v(m+1), p(m+1);
        vi path(m+1);
        for (int i=1; i<=n; i++){
            p[0] = i;
            int j0 = 0;
            vll minv(m+1, inf);
            vb used(m+1, false);
            do{
                used[j0] = true;
                int i0 = p[j0], j1;
                ll delta = inf;
                for (int j=1; j<=m; j++)
                    if (!used[j]){
                        ll cur = w[i0][j]-u[i0]-v[j];
                        if (cur < minv[j])
                            minv[j] = cur,  path[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j],  j1 = j;
                    }
                for (int j=0; j<=m; ++j)
                    if (used[j])
                        u[p[j]] += delta,  v[j] -= delta;
                    else
                        minv[j] -= delta;
                j0 = j1;
            }while (p[j0] != 0);
            do{
                int j1 = path[j0];
                p[j0] = p[j1];
                j0 = j1;
            }while(j0);
        }

        for(int i=1; i<=m; i++) M.pb({p[i], i});
        min_cost = -v[0];

        return;
    }
};
