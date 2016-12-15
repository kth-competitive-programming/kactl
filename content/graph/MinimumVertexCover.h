/**
 * Author: Johan Sannemo
 * Description: Finds a minimum vertex cover in a bipartite graph. The size is the same as the size of a maximum matching.
 */

#include "DFSMatching.h"

template<class G>
bool find2(int i, G &g) {
    trav(e, g[i])
        if (!seen[e]) {
            seen[e] = true;
            if (match[e] != -1) find2(match[e], g);
        }
    return 0;
}

template<class G>
vi dfs2(G &g, int a, int b) {
    int res = dfs_matching(g, a, b);
    seen.assign(b, false);
    vector<bool> lfound(a, true), rfound(b);
    trav(it, match) if (it != -1) lfound[it] = false;
    rep(i,0,a) if (lfound[i]) find2(i, g);
    rep(i,0,b)
        if (seen[i]) {
            rfound[i] = true;
            if (match[i] != -1) lfound[match[i]] = true;
        }
    vi cover;
    rep(i,0,a) if (lfound[i]) cover.push_back(i);
    rep(i,0,b) if (!rfound[i]) cover.push_back(a+i);
    return cover;
}
