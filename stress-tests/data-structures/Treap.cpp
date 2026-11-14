#include "../utilities/template.h"

#include "../../content/data-structures/Treap.h"

// l will have nodes <= i, r rest
void split2(Node* x, Node*& l, Node*& r, int i) {
	if (!x) return void(l = r = 0);
	push(x);
	if (i <= x->val) split2(x->l, l, x->l, i), r = x;
	else split2(x->r, x->r, r, i), l = x;
	pull(x);
}

mt19937 rng(10);
int ra(int hi) {
	return uniform_int_distribution<int>(0, hi)(rng);
}

int main() {
	srand(3);
	// Treaps as sets
	rep(it,0,1000) {
		vector<Node> nodes;
		vi exp;
		rep(i,0,10) {
			nodes.emplace_back(i*2+2);
			exp.emplace_back(i*2+2);
		}
		Node* root = 0;
		rep(i,0,10) merge(root, root, &nodes[i]);

		int v = rand() % 25;
		Node *d1, *d2;
		split2(root, d1, d2, v);
		int left = cnt(d1);
		int rleft = (int)(lower_bound(all(exp), v) - exp.begin());
		assert(left == rleft);
	}

	// move range
	rep(it,0,10000) {
		vector<Node> nodes;
		vi exp;
		rep(i,0,10) nodes.emplace_back(i);
		rep(i,0,10) exp.emplace_back(i);
		Node* n = 0;
		rep(i,0,10)
			merge(n, n, &nodes[i]);

		int i = ra(10), j = ra(10);
		if (i > j) swap(i, j);
		int k = ra(10);
		if (i < k && k < j) continue;

		move(n, i, j, k);

		int nk = (k >= j ? k - (j - i) : k);
		vi iv(exp.begin() + i, exp.begin() + j);
		exp.erase(exp.begin() + i, exp.begin() + j);
		exp.insert(exp.begin() + nk, all(iv));

		int ind = 0;
		each(n, [&](int x) {
			assert(x == exp[ind++]);
		});
	}

	// reverse range
	rep(it,0,10000) {
		vector<Node> nodes;
		vi exp;
		rep(i,0,10) nodes.emplace_back(i);
		rep(i,0,10) exp.emplace_back(i);
		Node* n = 0;
		rep(i,0,10)
			merge(n, n, &nodes[i]);

		int rounds = ra(10);
		// do multiple rounds to try and break lazy propagation
		rep(i,0,rounds) {
			int l = ra(9);
			int r = ra(9);
			if (r<l) swap(l,r);
			if (l==r) r++;
			reverse(exp.begin()+l, exp.begin()+r);
			rev(n, l, r);
		}

		int ind = 0;
		each(n, [&](int x) {
			assert(x == exp[ind++]);
		});
	}
	cout<<"Tests passed!"<<endl;
}
