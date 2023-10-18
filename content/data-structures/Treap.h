/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

struct Node {
  unsigned rnd() {
    static unsigned x = 71;
    return ++(x *= 0xdefaced);
  }
	Node *l = 0, *r = 0;
	int val, c = 1; unsigned y;
	Node(int val) : val(val), y(rnd()) {}
  void pull();
};
int cnt(Node* n) { return n ? n->c : 0; }
void Node::pull() { c = cnt(l) + cnt(r) + 1; }
template<class F> void each(Node* n, F f)
{ if (n) { each(n->l, f); f(n->val); each(n->r, f); } }

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto pa = split(n->l, k);
		n->l = pa.second;
		n->pull();
		return {pa.first, n};
	}
  auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
  n->r = pa.first;
  n->pull();
  return {n, pa.second};
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		l->pull();
		return l;
	}
  r->l = merge(l, r->l);
  r->pull();
  return r;
}

Node* ins(Node* t, Node* n, int pos) { // 0-base
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}

// Example application: move the range [l, r) to index k
// void move(Node*& t, int l, int r, int k) {
// 	Node *a, *b, *c;
// 	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
// 	if (k <= l) t = merge(ins(a, b, k), c);
// 	else t = merge(a, ins(c, b, k - r));
// }
