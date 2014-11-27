/**
* Description: General matching
* Author: github
* Source: github
* Date: today
*/
#include <stdio.h>
#include <string.h>
#define MAXV 1008
#define MAXE 200008
#define SBN (sizeof(bool) * (n + 1))
#define SIN (sizeof(int) * (n + 1))
struct Edge {
	int v, next;
	Edge(){}
	Edge(int _v, int _next):
	v(_v), next(_next){}
};
struct Graph {
	int n, match[MAXV], que[MAXV], pre[MAXV], base[MAXV];
	bool flag[MAXV], inBlossom[MAXV], inPath[MAXV];
	Edge edge[MAXE];
	int head[MAXV], size;
	inline void initg(int _n) {
		size = 0;
		n = _n;
		memset(head, -1, SIN);
	}
	inline void addEdge(int u, int v) {
		if (u == v) return;
		edge[size] = Edge(v, head[u]);
		head[u] = size++;
		edge[size] = Edge(u, head[v]);
		head[v] = size++;
	}
	int MaxMatch() {
		memset(match, -1, SIN);
		int i, j, ans = 0;
		for (i = 1; i <= n; ++i) {
			if (match[i] != -1) continue;
			for (j = head[i]; j != -1 && match[i] == -1; j = edge[j].next)
				if (match[edge[j].v] == -1) {
					match[edge[j].v] = i;
					match[i] = edge[j].v;
					ans++;
				}
		}
		for (i = 1; i <= n; ++i)
			if (match[i] == -1)
				ans += bfs(i);
				return ans;
	}
	int bfs(int p) {
	int i, j, u, v, b, front, rear;
	memset(pre, -1, SIN);
	memset(flag, 0, SBN);
	for (i = 1; i <= n; ++i)
		base[i] = i;
		front = rear = 0;
		que[rear++] = p;
		flag[p] = 1;
		while (front != rear) {
			u = que[front++];
			for (i = head[u]; i != -1; i = edge[i].next) {
				v = edge[i].v;
				if (base[u] != base[v] && v != match[u]) {
					if (v == p || (match[v] != -1 && pre[match[v]] != -1)) {
						b = contract(u, v);
						for (j = 1; j <= n; ++j) {
							if (inBlossom[base[j]]) {
								base[j] = b;
								if (flag[j] == 0) {
									flag[j] = 1;
									que[rear++] = j;
								}
							}
						}
					}
					else if (pre[v] == -1) {
						pre[v] = u;
						if (match[v] == -1) {
							argument(v);
							return 1;
						}
						else {
							que[rear++] = match[v];
							flag[match[v]] = 1;
						}
					}
				}
			}
		}
		return 0;
	}
	void argument(int u) {
	int v, k;
	while (u != -1) {
		v = pre[u];
		k = match[v];
		match[u] = v;
		match[v] = u;
		u = k;
	}
	}
	void changeBlossom(int b, int u) {
	int v;
	while (base[u] != b) {
		v = match[u];
		inBlossom[base[v]] = inBlossom[base[u]] = true;
		u = pre[v];
		if (base[u] != b)
			pre[u] = v;
	}
	}
	int contract(int u, int v) {
	memset(inBlossom, 0, SBN);
	int b = findBase(base[u], base[v]);
	changeBlossom(b, u);
	changeBlossom(b, v);
	if (base[u] != b)
		pre[u] = v;
		if (base[v] != b)
			pre[v] = u;
			return b;
	}
	int findBase(int u, int v) { 
	memset(inPath, 0, SBN);
	while (true) {
		inPath[u] = true;
		if (match[u] == -1)
			break;
			u = base[pre[match[u]]];
	}
	while(!inPath[v])
		v = base[pre[match[v]]];
		return v;
	}
}GP;
