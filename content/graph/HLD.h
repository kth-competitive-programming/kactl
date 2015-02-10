/**
 * Author: Johan Sannemo
 * Date: 2015-02-10
 * Source: folkore
 * Description: Decomposes a tree into vertex disjoint heavy paths and light edges such that the path from any leaf to the root contains at most log(n) light edges. The function of the HLD can be changed by modifying T, LOW and f.
 * Status: Tested at SPOJ
 */
#include <bits/stdc++.h>
#include "../data structures/SegmentTree.h"
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(it, v) for(auto it = v.begin(); \
		it != v.end(); ++it)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef vector<pii> vpi;

struct Node {
	int d, par, val, chain = -1, pos = -1;
};

struct Chain {
	int par, val;
	vector<int> nodes;
	Tree tree;
};

struct HLD {
	typedef int T;
	const T LOW = -(1<<29);
	void f(T& a, T b) { a = max(a, b); }

	vector<Node> nodes;
	vector<Chain> ked;

	HLD(vector<vpi>& g) : nodes(sz(g)) {
		dfs(0, -1, g, 0);
		trav(it, ked){
			it->tree.init(sz(it->nodes), 0);
			for(int ni : it->nodes)
				it->tree.update(nodes[ni].pos, nodes[ni].val);
		}
	}

	void update(int node, T val){
		Node& n = nodes[node];
		if(n.chain == -1) n.val = val;
		else ked[n.chain].tree.update(n.pos, val);
	}

	int pard(Node& nod){
		if(nod.par == -1) return -1;
		return nodes[nod.chain == -1 ? nod.par : ked[nod.chain].par].d;
	}

	// query all *edges* between n1, n2
	pair<T, int> query(int i1, int i2){
		T ans = LOW;
		while(i1 != i2){
			Node n1 = nodes[i1], n2 = nodes[i2];
			if(n1.chain != -1 && n1.chain == n2.chain){
				int lo = n1.pos, hi = n2.pos;
				if(lo > hi) swap(lo, hi);
				f(ans, ked[n1.chain].tree.query(lo, hi));
				i1 = i2 = ked[n1.chain].nodes[hi];
			} else {
				if(pard(n1) < pard(n2))
					n1 = n2, swap(i1, i2);
				if(n1.chain == -1)
					f(ans, n1.val), i1 = n1.par;
				else {
					Chain& c = ked[n1.chain];
					f(ans, n1.pos ? c.tree.query(n1.pos,
						sz(c.nodes)) : c.tree.s[1]);
					i1 = c.par;
				}
			}
		}
		return make_pair(ans, i1);
	}

	// query all *nodes* between n1, n2
	pair<T, int> query2(int i1, int i2){
		pair<T, int> ans = query(i1, i2);
		f(ans.first, nodes[ans.second].val);
		return ans;
	}

	pii dfs(int at, int par, vector<vpi>& g, int d){
		nodes[at].d = d; nodes[at].par = par;
		int sum = 1, ch, nod, sz;
		tuple<int,int,int> mx(-1,-1,-1);
		trav(it, g[at]){
			if(it->first == par) continue;
			tie(sz, ch) = dfs(it->first, at, g, d+1);
			nodes[it->first].val = it->second;
			sum += sz;
			mx = max(mx, make_tuple(sz, it->first, ch));
		}
		tie(sz, nod, ch) = mx;
		if(2*sz < sum) return pii(sum, -1);
		if(ch == -1){
			ch = sz(ked);
			ked.emplace_back();
		}
		nodes[nod].pos = sz(ked[ch].nodes);
		nodes[nod].chain = ch;
		ked[ch].par = at;
		ked[ch].nodes.push_back(nod);
		return pii(sum, ch);
	}
};
