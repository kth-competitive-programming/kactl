/**
 * Author: Tyler M
 * Date: 02/02/2024
 * Source: CP-Algorithms
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

struct node {
	int val, prior, sz = 1;
	node *left = nullptr, *right = nullptr;
	node(int val = 0): val(val), prior(rand()) {}
};

int getSz(node *cur) { return cur ? cur->sz : 0; }
void recalc(node *cur) { cur->sz = getSz(cur->left) + getSz(cur->right) + 1; }

pair<node*, node*> split(node *cur, int v) {
	if(!cur) return {nullptr, nullptr};
	node *left, *right;
	if(getSz(cur->left) >= v) {
		right = cur;
		auto [L, R] = split(cur->left, v);
		left = L, right->left = R;
		recalc(right);
	}
	else {
		left = cur;
		auto [L, R] = split(cur->right, v - getSz(cur->left) - 1);
		left->right = L, right = R;
		recalc(left);
	} 
	return {left, right};
}

node* merge(node *t1, node *t2) {
	if(!t1 || !t2) return t1 ? t1 : t2;
	node *res;
	if(t1->prior > t2->prior) {
		res = t1;
		res->right = merge(t1->right, t2);
	}
	else {
		res = t2;
		res->left = merge(t1, t2->left);
	}
	recalc(res);
	return res;
}
