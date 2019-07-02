/**
 * Author: 
 * Description: link-cut Tree.
 */
struct Node {
	bool flip = 0;
	Node *pp, *p, *c[2];
	// add stuff
	int val, cval;
	Node() { 
		pp = p = c[0] = c[1] = 0; 
		val = cval = 0;
	}
	void push() {
		if (flip) {
			if(c[0]) c[0]->flip ^= 1;
			if(c[1]) c[1]->flip ^= 1;
			swap(c[0], c[1]); flip = 0;
		}
		// add stuff
	}
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
		if (y) y->c[t] = c[!t];
		if (c[!t]) c[!t]->p = y;
		c[!t] = y;
		y->p = this;
		if (z) z->pull();
		if (y) y->pull();
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
		flip = 1;
		push();
		return this;
	} /// end-hash
};
struct LinkCut {
	vector<Node> node;
	LinkCut(int N): node(N) {}
	bool cut(int u, int v) { /// start-hash
		Node *x = &node[u], *y = &node[v];
		x->access();
		y->access();
		if (y->c[1] != x || x->c[0] != 0)
			return false;
		y->c[1] = 0;
		x->p = x->pp = 0;
		y->pull();
		return true;
	} /// end-hash
	bool isConnected(int u, int v) {
		Node *x = &node[u], *y = &node[v];
		x->access();
		y->access();
		return x == y || x->p != 0;
	}
	bool link(int u, int v) {
		Node *x = &node[u], *y = &node[v];
		if (isConnected(u, v)) return false;
		x->access();
		x->pp = y;
		return true;
	}
    void update(int u, int c) {
        node[u].access()->val+=c;
    }
	ll query(int u, int v) {
		node[v].access();
		return node[u].access()->cval;
	}
};