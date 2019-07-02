/**
 * Author: 
 * Description: link-cut Tree. Supports BBST-like 
 * augmentations. (Can be used in place of HLD).
 * Current implementation supports update value at a node,
 * and query max on a path.
 * Tested on: http://acm.timus.ru/problem.aspx?num=1553
 * Status: Passes existing fuzz tests (with function names modified).
 */
struct Node {
	bool flip = 0;
	Node *pp, *p, *c[2];
	// add stuff
	int val, cval, ind;
	Node() { 
		pp = p = c[0] = c[1] = 0; 
		val = cval = 0;
	}
	// lazy propogation
	void push() {
		if (flip) {
			if(c[0]) c[0]->flip ^= 1;
			if(c[1]) c[1]->flip ^= 1;
			swap(c[0], c[1]); flip = 0;
		}
		// add stuff
	}
	// combine values from children with self.
	void pull() {
		cval = val;
		if(c[0]) c[0]->push(), cval = max(cval, c[0]->cval); 
		if(c[1]) c[1]->push(), cval = max(cval, c[1]->cval);
		// add stuff
	}
	void rot(bool t) { /// start-hash
		Node *y = p, *z = y->p;
		if (z) z->c[z->c[1] == y] = this;
		p = z;
		y->c[t] = c[!t];
		if (c[!t]) c[!t]->p = y;
		c[!t] = y;
		y->p = this;
		if (z) z->pull();
		y->pull();
	} /// end-hash
	void xiao() {
		if (p) p->xiao(), pp = p->pp;
		push();
	}
	void splay() { /// start-hash
		xiao();
		Node *y, *z;
		while (p) {
			y = p; z = y->p;
			bool t1 = (y->c[1] == this);
			if (z) {
				bool t2 = (z->c[1] == y);
				if (t1 == t2) y->rot(t2), rot(t1);
				else rot(t1), rot(t2);
			} else rot(t1);
		}
		pull();
	} /// end-hash
	Node* access() {/// start-hash
		for (Node *y = 0, *z = this; z; y = z, z = z->pp) {
			z->splay();
			if (z->c[1]) z->c[1]->pp = z, z->c[1]->p = 0;
			z->c[1] = y;
			if (y) y->p = z;
			z->pull();
		}
		splay();
		return this;
	} /// end-hash
	Node* makeRoot() {
		access()->flip ^= 1;
		return this;
	}
};
struct LinkCut {
	vector<Node> node;
	LinkCut(int N): node(N) { rep(i, 0, N) node[i].ind = i; }
	int findRoot(int u) {
		Node *x = node[u].access();
		while(x->c[0]) x = x->c[0];
		return x->ind;
	}
	bool cut(int u, int v) { /// start-hash
		Node *y = node[v].makeRoot();
		Node *x = node[u].access();
		if (x->c[0] != y || y->c[1] != 0)
			return false;
		x->c[0] = y->p = y->pp = 0;
		x->pull();
		return true;
	} /// end-hash
	bool isConnected(int u, int v) {
		return findRoot(u) == findRoot(v);
	}
	bool link(int u, int v) {
		if (isConnected(u, v)) return false;
		node[u].makeRoot()->pp = &node[v];
		return true;
	}
	// Add c to node u.
	void update(int u, int c) {
		node[u].access()->val+=c;
	}
	// Find max on the path from u to v.
	ll query(int u, int v) {
		node[v].makeRoot();
		return node[u].access()->cval;
	}
};