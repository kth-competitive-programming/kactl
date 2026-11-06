/**
 * Author: Julio
 * Source: Um_nik code
 * Description: Treap, but persistent jejej
 * Time: O(log n)
 * Status: tested
 */
struct Node {
	int L, R;
	int sz;
	int x;
 
	Node() : L(-1), R(-1), sz(1), x() {}
};
const int SZ = (int)2e7 + 3;
Node tree[SZ];
int treeSz;
 
int getSize(int v) { return v == -1 ? 0 : tree[v].sz; }
int update(int v) {
	tree[v].sz = 1 + getSize(tree[v].L) + getSize(tree[v].R);
	return v;
}
int copy(int v) {
	if (v == -1) return -1;
	int u = treeSz++;
	tree[u] = tree[v];
	return u;
}
int newVertex(int x) {
	int v = treeSz++;
	tree[v].x = x;
	return v;
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
	return (ull)rng() % B;
}
int merge(int L, int R) {
	if (L == -1) return R;
	if (R == -1) return L;
	int lSz = tree[L].sz, rSz = tree[R].sz;
	if (myRand(lSz + rSz) < lSz) {
		int v = copy(L);
		tree[v].R = merge(tree[v].R, R);
		return update(v);
	} else {
		int v = copy(R);
		tree[v].L = merge(L, tree[v].L);
		return update(v);
	}
}
void split(int v, int k, int &L, int &R) {
	if (v == -1) {
		L = R = -1;
		return;
	}
	int lSz = getSize(tree[v].L);
	if (k <= lSz) {
		int u = copy(v);
		split(tree[u].L, k, L, tree[u].L);
		R = update(u);
	} else {
		int u = copy(v);
		split(tree[u].R, k - lSz - 1, tree[u].R, R);
		L = update(u);
	}
}