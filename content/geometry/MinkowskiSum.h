/**
 * Description: Returns the minkowski sum of a set of convex polygons
 * Time: O(n \log n)
 * Author: Tyler Marks
 * Source: CP-Algorithms 
 */
#define side(p) (p.x > 0 || (p.x == 0 && p.y > 0))
template<class P> 
vector<P> convolve(vector<vector<P>> &polys){
	P init; vector<P> dir;
	for(auto poly: polys) {
		int n = sz(poly);
		if(n) init = init + poly[0];
		if(n < 2) continue;
		rep(i, 0, n) dir.push_back(poly[(i+1)%n] - poly[i]);
	}
	if(size(dir) == 0) return { init };
	stable_sort(all(dir), [&](P a, P b)->bool {
		if(side(a) != side(b)) return side(a);
		return a.cross(b) > 0;
	});
	vector<P> sum; P cur = init;
	rep(i, 0, sz(dir))
		sum.push_back(cur), cur = cur + dir[i];
	return sum;
}