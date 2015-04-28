/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: KD-tree (2d, can be extended to 3d)
 * Status: Untested, but works for Stanford
 */

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include "Point.h"
using namespace std;

typedef long long ntype;
typedef Point<ntype> P;
const ntype INF = numeric_limits<ntype>::max();

// sorts points on x/y-coordinate
bool on_x(const P& a, const P& b) { return a.x < b.x; }
bool on_y(const P& a, const P& b) { return a.y < b.y; }

ntype pdist2(const P& a, const P& b) { return (a-b).dist2(); }

// bounding box for a set of points
struct bbox {
	ntype x0, x1, y0, y1;
	bbox() : x0(INF), x1(-INF), y0(INF), y1(-INF) {}

	void compute(const vector<P>& v) {
		for (P p : v) {
			x0 = min(x0, p.x); x1 = max(x1, p.x);
			y0 = min(y0, p.y); y1 = max(y1, p.y);
		}
	}

	// squared distance between a point and this bbox, 0 if inside
	ntype distance(const P& p) {
		if (p.x < x0) {
			if (p.y < y0) return pdist2(P(x0, y0), p);
			if (p.y > y1) return pdist2(P(x0, y1), p);
			else          return pdist2(P(x0, p.y), p);
		}
		else if (p.x > x1) {
			if (p.y < y0) return pdist2(P(x1, y0), p);
			if (p.y > y1) return pdist2(P(x1, y1), p);
			else          return pdist2(P(x1, p.y), p);
		}
		else {
			if (p.y < y0) return pdist2(P(p.x, y0), p);
			if (p.y > y1) return pdist2(P(p.x, y1), p);
			else          return 0;
		}
	}
};

struct kdnode {
	bool leaf;
	P pt; // if this is a leaf, the single point in it
	bbox bound;

	kdnode *first, *second;

	kdnode() : leaf(false), first(0), second(0) {}
	~kdnode() { delete first; delete second; }

	ntype intersect(const P& p) { return bound.distance(p); }

	void construct(vector<P>& vp)
	{
		bound.compute(vp);

		if (vp.size() == 1) {
			leaf = true;
			pt = vp[0];
		}
		else {
			// split on x if the bbox is wider than high (not best heuristic...)
			if (bound.x1-bound.x0 >= bound.y1-bound.y0)
				sort(vp.begin(), vp.end(), on_x);
			else
				sort(vp.begin(), vp.end(), on_y);

			// divide by taking half the array for each child (not
			// best performance with many duplicates in the middle)
			int half = vp.size()/2;
			vector<P> vl(vp.begin(), vp.begin()+half);
			vector<P> vr(vp.begin()+half, vp.end());
			first = new kdnode();   first->construct(vl);
			second = new kdnode();  second->construct(vr);            
		}
	}
};

struct kdtree {
	kdnode *root;

	kdtree(const vector<P>& vp) {
		vector<P> v(vp.begin(), vp.end());
		root = new kdnode();
		root->construct(v);
	}
	~kdtree() { delete root; }

	pair<ntype, P> search(kdnode *node, const P& p) {
		if (node->leaf) {
			// uncomment if we should not find the point itself:
			// if (p == node->pt) return INF;
			return make_pair(pdist2(p, node->pt), node->pt);
		}

		ntype bfirst = node->first->intersect(p);
		ntype bsecond = node->second->intersect(p);

		// search closest side first, other side if needed
		pair<ntype, P> best;
		if (bfirst < bsecond) {
			best = search(node->first, p);
			if (bsecond < best)
				best = min(best, search(node->second, p));
		}
		else {
			best = search(node->second, p);
			if (bfirst < best)
				best = min(best, search(node->first, p));
		}
		return best;
	}

	// find nearest point to a point, and its squared distance
	// (requires an arbitrary operator< for Point)
	pair<ntype, P> nearest(const P& p) {
		return search(root, p);
	}
};
