/**
 * Author: Unknown
 * Date: Unknown
 * Source: https://cp-algorithms.com/data_structures/treap.html
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data. Also supports
 *  range updates.
 * Time: $O(\log N)$ per split/merge
 * Status: stress-tested, tested on cses Substring Reversals and Cut and Paste
 */
#pragma once

struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1, rev = 0;
	Node(int val) : val(val), y(rand()) {}
};

int cnt(Node* n) { return n ? n->c : 0; }
void pull(Node* n) { if (n) n->c = cnt(n->l) + cnt(n->r)+1; }
void push(Node* n) {
	if (!n) return;
	if (n->rev) {
		swap(n->l, n->r);
		if (n->l) n->l->rev ^= 1;
		if (n->r) n->r->rev ^= 1;
		n->rev = 0;
	}
}

template<class F> void each(Node* n, F f) {
	if (n) { push(n);each(n->l, f);f(n->val);each(n->r, f); }
}

// Put i first nodes into l, the rest into r
void split(Node* x, Node*& l, Node*& r, int i) {
	if (!x) return void(l = r = 0);
	push(x);
	// replace cnt(x->l) with x->val for lower_bound(i)
	if (i <= cnt(x->l)) split(x->l, l, x->l, i), r = x;
	//                        and just i instead
	else split(x->r, x->r, r, i - cnt(x->l) - 1), l = x;
	pull(x);
}

// Append r to l, store it in x
void merge(Node*& x, Node* l, Node* r) {
	push(l), push(r);
	if (!l || !r) x = l ? l : r;
	else if (l->y < r->y) merge(r->l, l, r->l), x = r;
	else merge(l->r, l->r, r), x = l;
	pull(x);
}

void insert(Node*& t, Node* n, int pos) {
	Node* l, * r;
	split(t, l, r, pos), merge(l, l, n), merge(t, l, r);
}

// Example application: move the range [l, r) to index k
void move(Node*& t, int l, int r, int k) {
	Node* a, * b, * c;
	split(t, a, c, r), split(a, a, b, l), merge(t, a, c);
	if (k<=l) insert(t, b, k);
	else insert(t, b, k - r + l);
}

// Reverse the range [l, r)
void rev(Node*& t, int l, int r) {
	Node* a, * b, * c;
	split(t, a, c, r), split(a, a, b, l);
	b->rev ^= 1;
	merge(a, a, b), merge(t, a, c);
}
