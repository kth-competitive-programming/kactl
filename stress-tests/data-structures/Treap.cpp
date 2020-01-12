#include "../utilities/template.h"

#include "../../content/data-structures/Treap.h"

pair<Node*, Node*> split2(Node* n, int v) {
	if (!n) return {};
	if (n->val >= v) {
		auto pa = split2(n->l, v);
		n->l = pa.second;
		n->recalc();
		return {pa.first, n};
	} else {
		auto pa = split2(n->r, v);
		n->r = pa.first;
		n->recalc();
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
	cout<<"Tests passed!"<<endl;
}
