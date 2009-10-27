/**
 * Author: Lukas
 * Date: 2009-10-27
 * Source: folklore
 * Description: Treap is a binary search tree where each node
 * stores a secondary key. The tree is a heap according to the
 * secondary key. Secondary keys are random, hence this
 * datastructure is randomized. Expected running time of each
 * operation is $O(\log N)$.
 */
#pragma once
#include <vector>
using namespace std;

struct Node {
	int pr, key;
	Node* s[2];//sons
	Node* fat;//father
	Node(int k, int p) : pr(p), key(k) {
		s[0] = s[1] = NULL;
	}
	void set(int i, Node* val) {
		s[i] = val;
		if (s[i] != NULL)
			s[i]->fat = this;
	}
};
Node* root;
void rotate(Node *son) {
	Node *father = son->fat;
	bool type = (father->s[0] == son);
	father->set(!type, son->s[type]);
	if (father->fat != NULL)
		father->fat->set(father->fat->s[1] == father, son);
	else {
		son->fat = NULL;
		root = son;
	}
	son->set(type, father);
}
void insert(int a, int p) {
	if (root == NULL) {
		root = new Node(a, p);
		root->fat = NULL;
		return;
	}
	Node* x = root;
	while (x != NULL) {
		bool ok = (x->key <= a);
		if (x -> s[ok] == NULL) {
			x->set(ok, new Node(a, p));
			x = x->s[ok];
			break;
		}
		else x = x->s[ok];
	}
	while (x->fat != NULL) {
		if (x->pr <= x->fat->pr) break;
		rotate(x);
	}
}
void erase(int a) {
	Node* x = root;
	while (x != NULL) {
		if (x->key == a) break;
		x = x->s[x->key < a];
	}
	if (x == NULL) return;
	while (x->s[0] != NULL || x->s[1] != NULL) {
		if (x->s[0] == NULL) rotate(x->s[1]);
		else if (x->s[1] == NULL) rotate(x->s[0]);
		else rotate(x->s[x->s[0]->pr <= x->s[1]->pr]);
	}
	x->fat->set(x->fat->s[1] == x, NULL);
	delete x;
}
