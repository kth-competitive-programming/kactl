/**
 * Author: Maskrio
 * Date: -
 * License: -
 * Source: -
 * Description: Calculate flow
 * Time: O(E \times maxflow)
 * Status: -
 */
#pragma once

int sink, source;
const int maxn = 6e2 + 17, maxm = maxn * maxn + 17, inf = 1e9 + 17;
int head[maxn], to[maxm], prv[maxm], cap[maxm], cost[maxm], ecnt, mark[maxn];

void init() {
    memset(to,0,sizeof to);
    memset(cap,0,sizeof cap);
    memset(prv,0,sizeof prv);
    memset(cost,0,sizeof cost);
    memset(mark,0,sizeof mark);
	memset(head, -1, sizeof head);
    ecnt = 0;
}
void add(int v, int u, int vu, int uv = 0) {
	to[ecnt] = u, prv[ecnt] = head[v], cap[ecnt] = vu, head[v] = ecnt++;
	to[ecnt] = v, prv[ecnt] = head[u], cap[ecnt] = uv, head[u] = ecnt++;
}
int dfs(int v, int flow = inf) {
	if (v == sink || flow == 0) return flow;
	if (mark[v]) return 0;
	mark[v] = 1;
	for (int e = head[v]; e != -1; e = prv[e])
		if (cap[e]) {
			int x = dfs(to[e], min(flow, cap[e]));
			if (x)
				return cap[e] -= x, cap[e ^ 1] += x, x;
		}
	return 0;
}
int maxflow() {
	int ans = 0;
	for (int tmp; (tmp = dfs(source)); ans += tmp)
		memset(mark, 0, sizeof mark);
	return ans;
}