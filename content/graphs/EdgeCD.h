/**
 * Author: Luke Videckis
 * Date: 2024-05-21
 * Source: https://github.com/programming-team-code/programming_team_code/
 * Description: n/a
 * Time: $O(n \log n)$
 * Status: Untested
 */
#pragma once

template <class F> struct edge_cd {
	vector<vector<int>> adj;
	F f;
	vector<int> sub_sz;
	edge_cd(const vector<vector<int>>& a_adj, F a_f) : adj(a_adj), f(a_f), sub_sz((int)size(adj)) {
		dfs(0, (int)size(adj));
	}
	int find_cent(int u, int p, int siz) {
		sub_sz[u] = 1;
		for (int v : adj[u])
			if (v != p) {
				int cent = find_cent(v, u, siz);
				if (cent != -1) return cent;
				sub_sz[u] += sub_sz[v];
			}
		if (p == -1) return u;
		return 2 * sub_sz[u] >= siz ? sub_sz[p] = siz - sub_sz[u], u : -1;
	}
	void dfs(int u, int siz) {
		if (siz <= 2) return;
		u = find_cent(u, -1, siz);
		int sum = 0;
		auto it = partition(begin(adj[u]), end(adj[u]), [&](int v) {
			bool ret = 2 * sum + sub_sz[v] < siz - 1 && 3 * (sum + sub_sz[v]) <= 2 * (siz - 1);
			if (ret) sum += sub_sz[v];
			return ret;
		});
		f(adj, u, it - begin(adj[u]));
		vector<int> oth(it, end(adj[u]));
		adj[u].erase(it, end(adj[u]));
		dfs(u, sum + 1);
		swap(adj[u], oth);
		dfs(u, siz - sum);
	}
};