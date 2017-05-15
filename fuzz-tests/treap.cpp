#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/data-structures/Treap.h"

pair<Node*, Node*> split2(Node* n, int v) {
	if (!n) return {};
	if (n->val >= v) {
		auto pa = split2(n->l, v);
		n->l = pa.second;
		recalc(n);
		return {pa.first, n};
	} else {
		auto pa = split2(n->r, v);
		n->r = pa.first;
		recalc(n);
		return {n, pa.second};
	}
}

int ra() {
	static unsigned x;
	x *= 4176481;
	x += 193861934;
	return x >> 1;
}

int main() {
	srand(3);
	rep(it,0,1000) {
		vector<Node> nodes;
		vi exp;
		rep(i,0,10) {
			nodes.emplace_back(i*2+2);
			exp.emplace_back(i*2+2);
		}
		Node* n = 0;
		rep(i,0,10)
			n = merge(n, &nodes[i]);

		int v = rand() % 25;
		int left = cnt(split2(n, v).first);
		int rleft = (int)(lower_bound(all(exp), v) - exp.begin());
		assert(left == rleft);
	}

	rep(it,0,10000) {
		cerr << '.';
		vector<Node> nodes;
		vi exp;
		rep(i,0,10) nodes.emplace_back(i);
		rep(i,0,10) exp.emplace_back(i);
		Node* n = 0;
		rep(i,0,10)
			n = merge(n, &nodes[i]);

		int i = ra() % 11, j = ra() % 11;
		if (i > j) swap(i, j);
		int k = ra() % 11;
		if (i < k && k < j) continue;

		move(n, i, j, k);
		// cerr << i << ' ' << j << ' ' << k << endl;

		int nk = (k >= j ? k - (j - i) : k);
		vi iv(exp.begin() + i, exp.begin() + j);
		exp.erase(exp.begin() + i, exp.begin() + j);
		exp.insert(exp.begin() + nk, all(iv));

		int ind = 0;
		each(n, [&](int x) {
			// cerr << x << ' ';
			assert(x == exp[ind++]);
		});
		// cerr << endl;
	}
}
