/**
 * Author: Benq
 * Date: 2016-12-09
 * License: CC0
 * Description: Variant on Gabow's Impl of Edmond's Blossom Algorithm. 
    * General unweighted max matching with 1-based indexing. If 
    * \texttt{white[v] = 0} after \texttt{solve()} returns, \texttt{v} is part
    * of every max matching.
 * Time: O(NM), faster in practice
 * Source: 
	* https://github.com/koosaga/DeobureoMinkyuParty
	* https://www-m9.ma.tum.de/graph-algorithms/matchings-blossom-algorithm/index_en.html
	* https://codeforces.com/blog/entry/63630
	* https://github.com/yosupo06/library-checker-problems/blob/master/graph/general_matching/sol/correct.cpp
	* https://web.eecs.umich.edu/~pettie/matching/Gabow-general-matching-1976.pdf
 */
#pragma once

struct MaxMatching {
	int N; V<vi> adj;
	V<int> mate, first; vb white; vpi label;
	void init(int _N) { N = _N; adj = V<vi>(N+1); 
		mate = first = vi(N+1); label = vpi(N+1); white = vb(N+1); }
	void ae(int u, int v) { adj.at(u).pb(v), adj.at(v).pb(u); }
	int group(int x) { if (white[first[x]]) first[x] = group(first[x]);
		return first[x]; }
	void match(int p, int b) {
		swap(b,mate[p]); if (mate[b] != p) return;
		if (!label[p].s) mate[b] = label[p].f, match(label[p].f,b); // vertex label
		else match(label[p].f,label[p].s), match(label[p].s,label[p].f); // edge label
	}
	bool augment(int st) { assert(st);
		white[st] = 1; first[st] = 0; label[st] = {0,0};
		queue<int> q; q.push(st);
		while (!q.empty()) {
			int a = q.ft; q.pop(); // outer vertex
			each(b,adj[a]) { assert(b);
				if (white[b]) { // two outer vertices, form blossom
					int x = group(a), y = group(b), lca = 0;
					while (x||y) {
						if (y) swap(x,y);
						if (label[x] == pi{a,b}) { lca = x; break; }
						label[x] = {a,b}; x = group(label[mate[x]].first);
					}
					for (int v: {group(a),group(b)}) while (v != lca) {
						assert(!white[v]); // make everything along path white
						q.push(v); white[v] = true; first[v] = lca;
						v = group(label[mate[v]].first);
					}
				} else if (!mate[b]) { // found augmenting path
					mate[b] = a; match(a,b); white = vb(N+1); // reset
					return true;
				} else if (!white[mate[b]]) {
					white[mate[b]] = true; first[mate[b]] = b;
					label[b] = {0,0}; label[mate[b]] = pi{a,0};
					q.push(mate[b]);
				}
			}
		}
		return false;
	}
	int solve() {
		int ans = 0;
		FOR(st,1,N+1) if (!mate[st]) ans += augment(st);
		FOR(st,1,N+1) if (!mate[st] && !white[st]) assert(!augment(st));
		return ans;
	}
};