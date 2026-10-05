/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is a maximum independent set.
 * Status: stress-tested
 */
#pragma once

#include "HopcroftKarp.h"

pair<vi, vi> cover(vector<vi>& g, vi& r) {
	int n = sz(g), t = 0;
	vi cl(n), cr(sz(r)), q(n);
	for (int u : r) if (u != -1) cl[u] = 1;
	rep(i, 0, n) if (!cl[i]) q[t++] = i;
	rep(i, 0, t) for (int v : g[q[i]]) {
		cr[v] = 1;
		if (r[v] != -1 && cl[r[v]]) cl[q[t++] = r[v]] = 0;
	}
	return {cl, cr};
}
