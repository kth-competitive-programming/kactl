/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-11-02
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/geometry/rectilinear_mst.cc
 * Description: Given N points, returns up to 8*N edges, which are guaranteed
 * to contain the Manhattan MST. The Manhattan MST of a set of points is the
 * MST where the weight of the edge between any pair of points is the Manhattan
 * distance between the points. Edges are in the form (distance, src, dst). Use
 * a standard MST algorithm on the result to find the final MST. Modify `edges`
 * and `sweep` to support doubles.
 * Time: O(N log N)
 * Status: Fuzz-tested
 */
typedef Point<int> P;
vector<array<int, 3>> manhattanMST(vector<P> ps) {
	vi id(sz(ps));
	iota(all(id), 0);
	vector<array<int, 3>> edges;
	rep(s,0,2) {
		rep(t,0,2) {
			sort(all(id), [&](int i, int j) {
			     return (ps[i]-ps[j]).x < (ps[j]-ps[i]).y;});
			map<int, int> sweep;
			for (int i: id) {
				for (auto it = sweep.lower_bound(-ps[i].y);
					        it != sweep.end(); sweep.erase(it++)) {
					int j = it->second;
					auto d = ps[j] - ps[i];
					if (d.y < d.x) break;
					edges.push_back({abs(d.y) + abs(d.x), i, j});
				}
				sweep[-ps[i].y] = i;
			}
			trav(p,ps) swap(p.y, p.x);
		}
		trav(p,ps) p.x = -p.x;
	}
	return edges;
}
