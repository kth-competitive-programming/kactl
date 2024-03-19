/**
 * Author: Eu-Shaun Leong
 * Date: 2024-03-19
 * License: CC0
 * Source: me
 * Description: Range add update, range max query data structure with persistence.
 * Time: O(\log N).
 * Usage: Node* t0=new Node(0,L-1); t1=t0->update(A,B,C); t1->query(X,Y);
 * Status: stress-tested on https://codebreaker.xyz/problem/rarwall. Consider reducing memory further.
 */
#pragma once

struct Node{
	typedef ll T;
	T f(T a, T b) { return max(a,b); }
	int s,e;
	Node *l,*r;
	T v,ladd;
	Node(int s, int e, Node *l=NULL, Node *r=NULL, T v=0, T ladd=0) : s(s),e(e),l(l),r(r),v(v),ladd(ladd) {}
	Node* copy() { return new Node(s,e,l,r,v,ladd); }
	void selfUpdate(T nv) {
		v += nv;
		ladd += nv;
	}
	void prop(Node *n) {
		int m=(s+e)/2;
		l = n->l ? n->l->copy() : new Node(s,m);
		r = n->r ? n->r->copy() : new Node(m+1,e);
		l->selfUpdate(ladd); r->selfUpdate(ladd); ladd=0;
	}
	void update(Node *n, int x, int y, T nv){
        if (!n) n = copy();
		if (s==x&&e==y) { selfUpdate(nv); return; }
		int m=(s+e)/2;
		prop(n);
		if (x<=m) l->update(n->l,x,min(m,y),nv);
		if (y>m) r->update(n->r,max(m+1,x),y,nv);
		v=f(l->v,r->v);
	}
	Node* update(int x, int y, T nv){
		Node *n = copy();
		n->update(this,x,y,nv);
		return n;
	}
	T query(int x, int y){
        Node *n = copy();
		if (s==x&&e==y) return n->v;
		int m=(s+e)/2;
		prop(n);
		if (y<=m) return l->query(x,y);
		if (x>m) return r->query(x,y);
		return f(l->query(x,m),r->query(m+1,y));
	}
};