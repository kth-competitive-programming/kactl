/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Faster bipartite matching algorithm. Graph $g$ should be a list
 * of neighbours of the left partition, and $btoa$ should be a vector full of
 * -1's with size equal to the size of the right partition. Returns the size of
 * the matching. $btoa[i]$ will the match for vertex $i$ or $-1$ if it's not
 * matched. Time: O(EV) where $E$ is the number of edges and V is the number of
 * vertices.
 * Usage: vi ba(m, -1); hopcroftKarp(g, ba);
 * Time: O(\sqrt{V}E)
 */
#pragma once

bool dfs(int a, int layer, const vector<vi>& g, vi& btoa,
			vi& A, vi& B) {
	if (A[a] != layer) return 0;
	A[a] = -1;
	trav(b, g[a]) if (B[b] == layer + 1) {
		B[b] = -1;
		if (btoa[b] == -1 || dfs(btoa[b], layer+2, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(const vector<vi>& g, vi& btoa) {
	int res = 0;
	vi A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), -1);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		trav(a, btoa) if(a != -1) A[a] = -1;
		rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay += 2) {
			bool islast = 0;
			next.clear();
			trav(a, cur) trav(b, g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && B[b] == -1) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			trav(a, next) A[a] = lay+1;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		rep(a,0,sz(g)) {
			if(dfs(a, 0, g, btoa, A, B))
				++res;
		}
	}
}
