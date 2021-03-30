/**
 * Author: Philippe Legault
 * Date: 2016
 * License: MIT
 * Source: https://github.com/Bathlamos/delaunay-triangulation/
 * Description: Fast Delaunay triangulation.
 * Each circumcircle contains none of the input points.
 * There must be no duplicate points.
 * If all points are on a line, no triangles will be returned.
 * Should work for doubles as well, though there may be precision issues in 'circ'.
 * Returns triangles in order \{t[0][0], t[0][1], t[0][2], t[1][0], \dots\}, all counter-clockwise.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;
typedef struct Quad* Q;
typedef __int128_t lll; // (can be ll if coords are < 2e4)

struct Quad {
	bool mark; Q o, rot; int p;
	int F() { return r()->p; }
	Q r() { return rot->rot; }
	Q prev() { return rot->o->rot; }
	Q next() { return r()->prev(); }
};

bool circ(P p, P a, P b, P c) { // is p in the circumcircle?
	lll p2 = p.dist2(), A = a.dist2()-p2,
	    B = b.dist2()-p2, C = c.dist2()-p2;
	return p.cross(a,b)*C + p.cross(b,c)*A + p.cross(c,a)*B > 0;
}
Q makeEdge(int orig, int dest) {
	Q q[] = {new Quad{0,0,0,orig}, new Quad{0,0,0,-1},
	         new Quad{0,0,0,dest}, new Quad{0,0,0,-1}};
	rep(i,0,4)
		q[i]->o = q[-i & 3], q[i]->rot = q[(i+1) & 3];
	return *q;
}
void splice(Q a, Q b) {
	swap(a->o->rot->o, b->o->rot->o); swap(a->o, b->o);
}
Q connect(Q a, Q b) {
	Q q = makeEdge(a->F(), b->p);
	splice(q, a->next());
	splice(q->r(), b);
	return q;
}

pair<Q,Q> rec(int l, int r, const vi& ind, const vector<P>& s) {
	if (r - l <= 3) {
		Q a = makeEdge(ind[l], ind[l + 1]);
		if (r - l == 2) return { a, a->r() };
		Q b = makeEdge(ind[l + 1], ind[l + 2]);
		splice(a->r(), b);
		auto side = s[ind[l]].cross(s[ind[l + 1]], s[ind[l + 2]]);
		Q c = side ? connect(b, a) : 0;
		return {side < 0 ? c->r() : a, side < 0 ? c : b->r() };
	}

#define H(e) s[e->F()], s[e->p]
#define valid(e) (s[e->F()].cross(H(base)) > 0)
	Q A, B, ra, rb;
	int m = l + r >> 1;
	tie(ra, A) = rec(l, m, ind, s);
	tie(B, rb) = rec(m, r, ind, s);
	while ((s[B->p].cross(H(A)) < 0 && (A = A->next())) ||
	       (s[A->p].cross(H(B)) > 0 && (B = B->r()->o)));
	Q base = connect(B->r(), A);
	if (A->p == ra->p) ra = base->r();
	if (B->p == rb->p) rb = base;

#define DEL(e, init, dir) Q e = init->dir; if (valid(e)) \
		while (circ(s[e->dir->F()], H(base), s[e->F()])) { \
			Q t = e->dir; \
			splice(e, e->prev()); \
			splice(e->r(), e->r()->prev()); \
			delete e->rot->rot->rot, delete e->rot->rot, delete e->rot, delete e; \
			e = t; \
		}
	for (;;) {
		DEL(LC, base->r(), o);  DEL(RC, base, prev());
		if (!valid(LC) && !valid(RC)) break;
		if (!valid(LC) || (valid(RC) && circ(H(RC), H(LC))))
			base = connect(RC, base->r());
		else
			base = connect(base->r(), LC->r());
	}
	return { ra, rb };
}

vector<array<int, 3>> triangulate(const vector<P> &pts) {
	vi ind(sz(pts)); iota(all(ind), 0);
	sort(all(ind), [&](int i, int j){ return pts[i] < pts[j]; });
	assert(unique(all(ind), [&](int i, int j){ return pts[i] == pts[j]; }) == ind.end());
	if (sz(pts) < 2) return {};
	Q e = rec(0, sz(pts), ind, pts).first;
	vector<Q> q = {e}, rem; vector<int> temp;
	q.reserve(3 * sz(pts)), rem.reserve(3 * sz(pts)), temp.reserve(3 * sz(pts));
	int qi = 0;
	while (pts[e->o->F()].cross(pts[e->F()], pts[e->p]) < 0) e = e->o;
#define ADD { Q c = e; do { c->mark = 1; temp.push_back(c->p); \
	q.push_back(c->r()); rem.push_back(c); c = c->next(); } while (c != e); }
	ADD; temp.clear();
	while (qi < sz(q)) if (!(e = q[qi++])->mark) ADD;
	assert((int)temp.size() % 3 == 0);
	for(auto e: rem) delete e->rot, delete e;
	vector<array<int, 3>> res;
	for(int i = 0; i < sz(temp); i += 3) if(pts[temp[i]].cross(pts[temp[i + 1]], pts[temp[i + 2]]) > 0)
		res.push_back({temp[i], temp[i + 1], temp[i + 2]});
	return res;
}
