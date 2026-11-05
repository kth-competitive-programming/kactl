
int segTreeOp(int a, int b) { return max(a, b); }
int segTreeE() { return INT_MIN; }

#include "../../content/data-structures/SegmentTree.h"

using MaxTree = SegTree<int, segTreeOp, segTreeE>;

typedef vector<pii> vpi;

struct Node {
	int d, par, val, chain = -1, pos = -1;
};

struct Chain {
	int par, val;
	vector<int> nodes;
	MaxTree tree{0};
};

struct HLD {
	typedef int T;
	const T LOW = -(1<<29);
	void f(T& a, T b) { a = max(a, b); }

	vector<Node> V;
	vector<Chain> C;

	HLD(vector<vpi>& g) : V(sz(g)) {
		dfs(0, -1, g, 0);
		for(auto &c: C) {
			c.tree = MaxTree(sz(c.nodes));
			for (int ni : c.nodes)
				c.tree.set(V[ni].pos, V[ni].val);
		}
	}

	void update(int node, T val) {
		Node& n = V[node]; n.val = val;
		if (n.chain != -1) C[n.chain].tree.set(n.pos, val);
	}

	int pard(Node& nod) {
		if (nod.par == -1) return -1;
		return V[nod.chain == -1 ? nod.par : C[nod.chain].par].d;
	}

	// query all *edges* between n1, n2
	pair<T, int> query(int i1, int i2) {
		T ans = LOW;
		while(i1 != i2) {
			Node n1 = V[i1], n2 = V[i2];
			if (n1.chain != -1 && n1.chain == n2.chain) {
				int lo = n1.pos, hi = n2.pos;
				if (lo > hi) swap(lo, hi);
				f(ans, C[n1.chain].tree.prod(lo, hi));
				i1 = i2 = C[n1.chain].nodes[hi];
			} else {
				if (pard(n1) < pard(n2))
					n1 = n2, swap(i1, i2);
				if (n1.chain == -1)
					f(ans, n1.val), i1 = n1.par;
				else {
					Chain& c = C[n1.chain];
					f(ans, n1.pos ? c.tree.prod(n1.pos, sz(c.nodes))
					              : c.tree.prod(0, sz(c.nodes)));
					i1 = c.par;
				}
			}
		}
		return make_pair(ans, i1);
	}

	// query all *nodes* between n1, n2
	pair<T, int> query2(int i1, int i2) {
		pair<T, int> ans = query(i1, i2);
		f(ans.first, V[ans.second].val);
		return ans;
	}

	pii dfs(int at, int par, vector<vpi>& g, int d) {
		V[at].d = d; V[at].par = par;
		int sum = 1, ch, nod, sz;
		tuple<int,int,int> mx(-1,-1,-1);
		for(auto &e: g[at]){
			if (e.first == par) continue;
			tie(sz, ch) = dfs(e.first, at, g, d+1);
			V[e.first].val = e.second;
			sum += sz;
			mx = max(mx, make_tuple(sz, e.first, ch));
		}
		tie(sz, nod, ch) = mx;
		if (2*sz < sum) return pii(sum, -1);
		if (ch == -1) { ch = sz(C); C.emplace_back(); }
		V[nod].pos = sz(C[ch].nodes);
		V[nod].chain = ch;
		C[ch].par = at;
		C[ch].nodes.push_back(nod);
		return pii(sum, ch);
	}
};
