/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: Simple bipartite matching algorithm. Graph $g$ should be a list
 * of neighbours of the left partition, and $btoa$ should be a vector full of
 * -1's with size equal to the size of the right partition. Returns the size of
 * the matching. $btoa[i]$ will the match for vertex $i$ or $-1$ if it's not
 * matched. Time: O(EV) where $E$ is the number of edges and V is the number of
 * vertices.
 * Usage: vi ba(m, -1); dfsMatching(g, ba);
 * Status: works
 */
#pragma once

bool find(int j, const vector<vi>& g, vi& btoa, vi& vis) {
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	trav(e, g[di])
		if (!vis[e] && find(e, g, btoa, vis)) {
			btoa[e] = di;
			return 1;
		}
	return 0;
}
int dfsMatching(const vector<vi> &g, vi& btoa) {
	vi vis;
	rep(i,0,sz(g)) {
		vis.assign(sz(btoa), 0);
		trav(j,g[i])
			if (find(j, g, btoa, vis)) {
				btoa[j] = i;
				break;
			}
	}
	return sz(btoa) - (int)count(all(btoa), -1);
}
