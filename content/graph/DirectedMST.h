/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-05-10
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/graph/arborescence.cc
 * Description: Edmonds' algorithm for finding the minimum spanning
 * tree/arborescence of a directed graph, given a root node. Returns (weight, parents), where
 * parents[root] = -1. If no MST exists, returns -1, \{\}.
 * Time: O(E \log V)
 * Status: Fuzz-tested, also tested on NWERC 2018 fastestspeedrun
 */
#pragma once

#include "../data-structures/UnionFind.h"

struct Edge { int a, b; ll w; };
struct SkewHeap {
	struct Node {
		Node *l, *r;
		Edge key;
		ll delta;
	} * root = 0;
	void prop(Node *a) {
		a->key.w += a->delta;
		if (a->l) a->l->delta += a->delta;
		if (a->r) a->r->delta += a->delta;
		a->delta = 0;
	}
	Node *merge(Node *a, node *b) {
		if (!a || !b) return a ? a : b;
		prop(a), prop(b);
		if (a->key.w > b->key.w) swap(a, b);
		swap(a->l, (a->r = merge(b, a->r)));
		return a;
	}
	void push(Edge e) { root = merge(root, new Node{0,0,e,0}); }
	void pop() { prop(root), root = merge(root->l, root->r); }
	Edge top() { prop(root); return root->key; }
	bool empty() { return !root; }
	void add(ll delta) { root->delta += delta; }
	void merge(SkewHeap x) { root = merge(root, x.root); }
};
struct DMST {
	vector<Edge> g;
	int n;
	DMST(int _n): n(_n){}
	void addEdge(int a, int b, ll w) { g.push_back({a, b, w}); }
	pair<ll, vi> solve(int r) {
		UF uf(n);
		vector<SkewHeap> heap(n);
		trav(e,g) heap[e.b].push(e);
		ll res = 0;
		vi seen(n, -1), path(n), par(n, -1);
		seen[r] = r;
		rep(s,0,n) {
			int u = s, qi = 0, w;
			while (seen[u] < 0) {
				path[qi++] = u, seen[u] = s;
				if (heap[u].empty()) return {-1, {}};
				Edge e = heap[u].top();
				heap[u].add(-e.w), heap[u].pop();
				res += e.w, u = uf.find(e.a);
				par[e.b] = e.a;
				if (seen[u] == s) {
					SkewHeap cyc;
					do cyc.merge(heap[w = path[--qi]]);
					while (uf.join(u, w));
					u = uf.find(u);
					heap[u] = cyc, seen[u] = -1;
				}
			}
		}
		return {res, par};
	}
};
