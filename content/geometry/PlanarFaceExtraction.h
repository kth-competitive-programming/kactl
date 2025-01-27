/**
 * Author: Tyler Marks
 * Source: unknown
 * Description: Given a planar graph and where the points are,
 * extract the set of faces that the graph makes. The inner faces
 * will be returned in counterclockwise order, and the outermost
 * face will be returned in clockwise order.
 * Time: O(E log E)
 * Status: tested on SER 20XX: Funhouse
 */

template<class P>
vector<vector<P>> extract_faces(vvi adj, vector<P> pts) {
	int n = sz(pts);
	#define cmp(i) [&](int pi, int qi) -> bool { \
		P p = pts[pi] - pts[i], q = pts[qi] - pts[i]; \
		bool sideP = p.y < 0 || (p.y == 0 && p.x < 0); \
		bool sideQ = q.y < 0 || (q.y == 0 && q.x < 0); \
		if(sideP != sideQ) return sideP; \
		return p.cross(q) > 0; }
	rep(i, 0, n)
		sort(all(adj[i]), cmp(i));
	vii ed;
	rep(i, 0, n) for(int j: adj[i])
		ed.emplace_back(i, j);
	sort(all(ed));
	auto get_idx = [&](int i, int j) -> int {
		return lower_bound(all(ed), pii(i, j))-begin(ed);
	};
	vector<vector<P>> faces;
	vi used(sz(ed));
	rep(i, 0, n) for(int j: adj[i]) {
		if(used[get_idx(i, j)])
			continue;
		used[get_idx(i, j)] = true;
		vector<P> face = {pts[i]};
		int prv = i, cur = j;
		while(cur != i) {
			face.push_back(pts[cur]);
			auto it = lower_bound(all(adj[cur]), prv, cmp(cur));
			if(it == begin(adj[cur]))
				it = end(adj[cur]);
			prv = cur, cur = *prev(it);
			used[get_idx(prv, cur)] = true;
		}
		faces.push_back(face);
	}
	#undef cmp
	return faces;
}