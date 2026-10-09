#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/graph/BellmanFord.h"

// Plain O(VE) Bellman-Ford: V-1 rounds, then everything reachable from
// a still-relaxable edge gets -inf.
vector<ll> naive(int n, vector<Ed>& eds, int s) {
	vector<ll> d(n, inf);
	d[s] = 0;
	rep(i,0,n-1) for (Ed e : eds)
		if (d[e.a] != inf && d[e.a] + e.w < d[e.b])
			d[e.b] = d[e.a] + e.w;
	vi neg(n);
	for (Ed e : eds)
		if (d[e.a] != inf && d[e.a] + e.w < d[e.b])
			neg[e.b] = 1;
	rep(i,0,n) for (Ed e : eds)
		if (neg[e.a]) neg[e.b] = 1;
	rep(i,0,n) if (neg[i]) d[i] = -inf;
	return d;
}

int main() {
	rep(it,0,100000) {
		int n = randRange(1, 15);
		int m = randRange(0, 30);
		int maxw = randRange(1, 10);
		int neg = randRange(0, maxw + 1);
		vector<Ed> eds;
		rep(i,0,m) {
			int a = randRange(n), b = randRange(n);
			int w = randRange(-neg, maxw + 1);
			eds.push_back({a, b, w});
		}
		int s = randRange(n);
		vector<ll> ref = naive(n, eds, s);
		vector<Node> nodes(n);
		bellmanFord(nodes, eds, s);
		rep(i,0,n) {
			Node& v = nodes[i];
			assert(v.dist == ref[i]);
			if (v.dist == inf || (i == s && v.dist == 0)) continue;
			// prev must name a predecessor along an actual edge, consistent with dist
			assert(v.prev != -1);
			bool ok = false;
			for (Ed e : eds) if (e.a == v.prev && e.b == i) {
				if (v.dist == -inf) ok |= nodes[e.a].dist == -inf;
				else ok |= nodes[e.a].dist != inf && nodes[e.a].dist + e.w == v.dist;
			}
			assert(ok);
		}
	}
	cout << "Tests passed!" << endl;
}
