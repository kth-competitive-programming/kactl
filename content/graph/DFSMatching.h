/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: This is a simple matching algorithm but should
 * be just fine in most cases. Graph $g$ should be a list of
 * neighbours of the left partition, and $btoa$ should be
 * a vector with size equal to the size of the right partition.
 * If you want to get the matched pairs, $btoa[i]$ contains
 * match for vertex $i$ on the right side or $-1$ if it's not
 * matched.
 * Time: O(EV) where $E$ is the number of edges and V is the number of vertices.
 * Usage: vi ba(m, -1); dfsMatching(g, ba);
 * Status: works
 */
#pragma once

bool find(int j, vector<vi>& g, vi& btoa, vector<bool>& vis) {
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	trav(e, g[di])
		if (!vis[e] && find(e, g, btoa, vis)) {
			btoa[e] = di;
			return 1;
		}
	return 0;
}
int dfsMatching(vector<vi> g, vi& btoa) {
	rep(i,0,sz(g)) {
		vector<bool> vis(sz(btoa));
		trav(j,g[i])
			if (find(j, g, btoa, vis)) {
				btoa[j] = i;
				break;
			}
	}
	return sz(btoa) - (int)count(all(btoa), -1);
}
