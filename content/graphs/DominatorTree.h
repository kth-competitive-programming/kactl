/**
 * Author: Tyler Marks (based on UCF PT)
 * Description: Builds a dominator tree on a directed graph. Output tree is a parent array with $src$ as the root.
 * Time: O(V+E)
 * Status: Untested
 */
#pragma once

vi getDomTree(vvi &adj, int src) {
	int n = sz(adj), t = 0;
	vvi revAdj(n), child(n), sdomChild(n);
	vi label(n, -1), revLabel(n), sdom(n), idom(n), par(n), best(n);

	auto dfs = [&](int cur, auto &dfs) -> void {
		label[cur] = t, revLabel[t] = cur;
		sdom[t] = par[t] = best[t] = t; t++;
		for(int nxt: adj[cur]) {
			if(label[nxt] == -1) {
				dfs(nxt, dfs);
				child[label[cur]].push_back(label[nxt]);
			}
			revAdj[label[nxt]].push_back(label[cur]);
		}
	};
	dfs(src, dfs);

	auto get = [&](int x, auto &get) -> int {
		if(par[x] != x) {
			int t = get(par[x], get);
			par[x] = par[par[x]];
			if(sdom[t] < sdom[best[x]]) best[x] = t;  
		}
		return best[x];
	};

	for(int i = t-1; i >= 0; i--) {
		for(int j: revAdj[i]) sdom[i] = min(sdom[i], sdom[get(j, get)]);
		if(i > 0) sdomChild[sdom[i]].push_back(i);
		for(int j: sdomChild[i]) {
			int k = get(j, get);
			if(sdom[j] == sdom[k]) idom[j] = sdom[j];
			else idom[j] = k;
		}
		for(int j: child[i]) par[j] = i;
	}

	vi dom(n);
	rep(i, 1, t) {
		if(idom[i] != sdom[i]) idom[i] = idom[idom[i]];
		dom[revLabel[i]] = revLabel[idom[i]];
	}

	return dom;
}