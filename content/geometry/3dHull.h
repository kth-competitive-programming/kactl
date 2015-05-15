/**
 * Author: Unknown
 * Date: Unknown
 * Source: tinyKACTL
 * Description: 3D convex hull. Requires the hull to have positive volume.
 * Arbitrarily triangulates the surface of the hull. Untested!
 * Usage:
 * Status: not tested
 * Time: O(n^2)
 */
#include "Point3D.h"

struct ABC {
	int a, b, c; ABC(int a, int b, int c) : a(a), b(b), c(c) {}
	bool operator<(const ABC &o) const {
		return make_tuple(a,b,c) < make_tuple(o.a,o.b,o.c);
	}
};

typedef double T; // e.g.
typedef Point3D<T> P3;
bool convex_hull_space(vector<P3>& p, list<ABC>& trilist) {
	int n = sz(p);
	int a, b, c; // Find a proper tetrahedron (could use an eps)
	for (a = 1; a < n; ++a)
		if ((p[a] - p[0]).dist2() != T()) break;
	for (b = a + 1; b < n; ++b)
		if ((p[a] - p[0]).cross(p[b] - p[0]).dist2()) break;
	for (c = b + 1; c < n; ++c) if ( (p[a] - p[0]).
			cross(p[b] - p[0]).dot(p[c] - p[0]) != T()) break;
	if (c >= n) return false; // same plane!
	if ((p[a] - p[0]).cross(p[b] - p[0]).dot(p[c] - p[0]) > T())
		swap(a, b);
	trilist.emplace_back(0, a, b);
	trilist.emplace_back(0, b, c);
	trilist.emplace_back(0, c, a);
	trilist.emplace_back(a, c, b);
	rep(i,1,n) {
		auto it = trilist.begin();
		set<pii> edges;
		P3 P = p[i];
		while (it != trilist.end()) {
			int a = it->a, b = it->b, c = it->c;

			P3 A = p[a], B = p[b], C = p[c];
			P3 normal = (B - A).cross(C - A);
			T d = normal.dot(P - A);
			if (d > T()) {
				edges.insert(pii(a, b));
				edges.insert(pii(b, c));
				edges.insert(pii(c, a));
				trilist.erase(it++); // ugly!!
			} else ++it;
		}
		trav(j, edges)
			if (edges.count(pii(j.second, j.first)) == 0)
				trilist.emplace_back(i, j.first, j.second);
	}
	return true;
}
