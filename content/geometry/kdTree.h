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

typedef long long T;
typedef Point<T> P;
const T INF = numeric_limits<T>::max();

bool on_x(const P& a, const P& b) { return a.x < b.x; }
bool on_y(const P& a, const P& b) { return a.y < b.y; }

struct Node {
	P pt; // if this is a leaf, the single point in it
	T x0, x1, y0, y1; // bounds
	Node *first = 0, *second = 0;

	T distance(const P& p) { // min squared distance to a point
		T x = (p.x < x0 ? x0 : p.x > x1 ? x1 : p.x);
		T y = (p.y < y0 ? y0 : p.y > y1 ? y1 : p.y);
		return (P(x,y) - p).dist2();
	}

	Node(vector<P>&& vp) : pt(vp[0]), x0(INF), x1(-INF),
			y0(INF), y1(-INF) {
		for (P p : vp) {
			x0 = min(x0, p.x); x1 = max(x1, p.x);
			y0 = min(y0, p.y); y1 = max(y1, p.y);
		}
		if (vp.size() > 1) {
			// split on x if the box is wider than high (not best heuristic...)
			if (x1 - x0 >= y1 - y0)
				sort(vp.begin(), vp.end(), on_x);
			else
				sort(vp.begin(), vp.end(), on_y);

			// divide by taking half the array for each child (not
			// best performance with many duplicates in the middle)
			int half = sz(vp)/2;
			first = new Node({vp.begin(), vp.begin() + half});
			second = new Node({vp.begin() + half, vp.end()});
		}
	}
};

struct KDTree {
	Node *root;
	KDTree(const vector<P>& vp) : root(new Node({all(vp)})) {}

	pair<T, P> search(Node *node, const P& p) {
		if (!node->first) {
			// uncomment if we should not find the point itself:
			// if (p == node->pt) return INF;
			return make_pair((p - node->pt).dist2(), node->pt);
		}

		T bfirst = node->first->distance(p);
		T bsecond = node->second->distance(p);

		// search closest side first, other side if needed
		pair<T, P> best;
		if (bfirst < bsecond) {
			best = search(node->first, p);
			if (bsecond < best.first)
				best = min(best, search(node->second, p));
		}
		else {
			best = search(node->second, p);
			if (bfirst < best.first)
				best = min(best, search(node->first, p));
		}
		return best;
	}

	// find nearest point to a point, and its squared distance
	// (requires an arbitrary operator< for Point)
	pair<T, P> nearest(const P& p) {
		return search(root, p);
	}
};
