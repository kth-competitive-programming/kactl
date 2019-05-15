#pragma once
#include "../data-structures/UnionFind.h"

struct edge { ll a, b, w; };
struct skew_heap {
	struct node {
		node *l, *r;
		edge key;
		ll delta;
	} * root;
	skew_heap() : root(0) {}
	void prop(node *a) {
		a->key.w += a->delta;
		if (a->l) a->l->delta += a->delta;
		if (a->r) a->r->delta += a->delta;
		a->delta = 0;
	}
	node *merge(node *a, node *b) {
		if (!a || !b) return a ? a : b;
		prop(a), prop(b);
		if (a->key.w > b->key.w) swap(a, b);
		swap(a->l, (a->r = merge(b, a->r)));
		return a;
	}
	void push(edge key) {
		node *n = new node();
		*n = {0, 0, key, 0};
		root = merge(root, n);
	}
	void pop() { prop(root), root = merge(root->l, root->r); }
	edge top() { prop(root); return root->key; }
	bool empty() { return !root; }
	void add(ll delta) { root->delta += delta; }
	void merge(skew_heap x) { root = merge(root, x.root); }
};

const ll INF = 1e18;
struct graph {
	vector<edge> g;
	ll n;
	graph(int _n): n(_n){}
	void add_edge(ll a, ll b, ll w) { g.push_back({a, b, w}); }
	ll solve(ll r) {
		UF uf(n);
		vector<skew_heap> heap(n);
		trav(e, g) heap[e.b].push(e);
		ll res = 0;
		vector<ll> seen(n, -1);
		seen[r] = r;
		rep(s,0,n){
			stack<ll> path;
			ll v = 0, w = 0;
			for (ll u = s; seen[u] < 0; u = uf.find(v)) {
				path.push(u), seen[u] = s;
				if (heap[u].empty()) return INF;
				edge min_e = heap[u].top();
				res += min_e.w;
				heap[u].add(-min_e.w), heap[u].pop();
				v = uf.find(min_e.a);
				if (seen[v] == s) {
					skew_heap tmp;
					do {
						w = path.top(), path.pop();
						tmp.merge(heap[w]);
					} while (uf.join(v, w));
					heap[uf.find(v)] = tmp, seen[uf.find(v)] = -1;
				}
			}
		}
		return res;
	}
};