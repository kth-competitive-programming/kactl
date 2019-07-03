/**
 * Author: 
 * Description: link-cut Tree. Supports BST-like 
 * augmentations. (Can be used in place of HLD).
 * Current implementation supports update value at a node,
 * and query max on a path.
 * Tested on: http://acm.timus.ru/problem.aspx?num=1553
 * Status: Passes existing fuzz tests (with function names modified).
 */
struct Node {
	bool flip = 0;
	Node *pp, *p, *c[2]; // path parent, parent, children
	// add stuff
	int val = 0, cval = 0, ind;
	Node() { pp = p = c[0] = c[1] = 0; }
	void push() {
		if (flip) {
			rep(i, 0, 2) if(c[i]) c[i]->flip ^= 1;
			swap(c[0], c[1]); flip = 0;
		}
	}
	void pull() {
		cval = val;
		rep(i, 0, 2) if(c[i]) c[i]->push(), cval = max(cval, c[i]->cval);
	}
	void rot(bool t) {
		Node *y = p, *z = y->p;
		if (z) z->c[z->c[1] == y] = this;
		y->c[!t] = c[t];
		if (c[t]) c[t]->p = y;
		c[t] = y; p = z;
		y->p = this;
		y->pull();
	}
	void xiao() {
		if (p) p->xiao(), pp = p->pp;
		push();
	}
	void splay() {
		xiao();
		while (p) {
			Node* y = p; Node *z = y->p;
			bool t1 = (y->c[1] != this);
			if (z) {
				bool t2 = (z->c[1] != y);
				if (t1 == t2) y->rot(t2), rot(t1);
				else rot(t1), rot(t2);
			} else rot(t1);
		}
		pull();
	}
	Node* access() {
		for (Node *y = 0, *z = this; z; y = z, z = z->pp) {
			z->splay();
			if (z->c[1]) z->c[1]->pp = z, z->c[1]->p = 0;
			z->c[1] = y;
			if (y) y->p = z;
			z->pull();
		}
		splay();
		return this;
	}
	Node* makeRoot() {
		access()->flip ^= 1;
		return this;
	}
};
struct LinkCut {
	vector<Node> nodes;
	LinkCut(int N) : nodes(N) { rep(i, 0, N) nodes[i].ind = i; }
	int findRoot(int u) {
		Node *x = nodes[u].access();
		while(x->c[0]) x = x->c[0];
		return x->ind;
	}
	bool cut(int u, int v) { /// start-hash
		Node *y = nodes[v].makeRoot();
		Node *x = nodes[u].access();
		if (x->c[0] != y || y->c[1])
			return false;
		x->c[0] = y->p = y->pp = 0;
		x->pull();
		return true;
	} /// end-hash
	bool isConnected(int u, int v) { return findRoot(u) == findRoot(v); }
	bool link(int u, int v) {
		if (isConnected(u, v)) return false;
		nodes[u].makeRoot()->pp = &nodes[v];
		return true;
	}
	void update(int u, int c) {
		nodes[u].access()->val += c;
	}
	int query(int u, int v) { // Find max on the path from u to v.
		nodes[v].makeRoot();
		return nodes[u].access()->cval;
	}
};
