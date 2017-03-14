/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 */
#pragma once
#include <cstdlib>
#include <utility>
using namespace std;

struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1;
	Node(int val) : val(val), y(rand()) {}
};

int cnt(Node* n) { return n ? n->c : 0; }
void recalc(Node* n) { n->c = cnt(n->l) + cnt(n->r) + 1; }

template<class F> void each(Node* n, F f) {
	if (n) { each(n->l, f); f(n->val); each(n->r, f); }
}

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	if (cnt(n->l) >= k) {
		auto pa = split(n->l, k);
		n->l = pa.second;
		recalc(n);
		return {pa.first, n};
	} else {
		auto pa = split(n->r, k - cnt(n->l) - 1);
		n->r = pa.first;
		recalc(n);
		return {n, pa.second};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		recalc(l);
		return l;
	} else {
		r->l = merge(l, r->l);
		recalc(r);
		return r;
	}
}

// Example application: cyclically shift [l, r) left by k steps
Node* shift(Node* t, int l, int r, int k) {
	k %= r - l;
	auto a = split(t, l), b = split(a.second, r - l),
		c = split(b.first, k);
	return merge(a.first, merge(merge(c.second, c.first), b.second));
}
