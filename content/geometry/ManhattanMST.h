/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-11-02
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/geometry/rectilinear_mst.cc
 * Description: Returns up to 8*N edges, which are guaranteed to contain the
 * Manhattan MST. Edges are in the form (distance, src, dst). Use a standard MST algorithm on the result to find the final MST.
 * Time: O(N log N)
 * Status: Fuzz-tested
 */
typedef Point<int> P;
vector<array<int, 3>> manhattanMST(vector<P> ps) {
	vector<int> id(sz(ps));
	iota(all(id), 0);
	vector<array<int, 3>> edges;
	rep(s,0,2) {
		rep(t,0,2) {
			sort(all(id), [&](int i, int j) {
					return (ps[i]-ps[j]).x < (ps[j]-ps[i]).y;});
			map<double, int> sweep;
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
			for (auto &p: ps) p = P(p.y, p.x);
		}
		for (auto &p: ps) p = P(-p.x, p.y);
	}
	return edges;
}
