#include "../utilities/template.h"

// #include "../../content/data-structures/MoQueries.h"

int curL = 0, curR = 0, ops = 0;
void add(int ind) {
	assert(ind == curR || ind == curL - 1 || curL == curR);
	if (curL == curR) curL = ind, curR = ind + 1;
	else if (ind == curR) curR++;
	else curL--;
	ops++;
}
void del(int ind) {
	assert(ind == curR - 1 || ind == curL);
	if (ind == curR - 1) curR--;
	else curL++;
	assert(curL <= curR);
	ops++;
}

int calc() {
	return curL == curR ? -1 : curL + (curR - curL) * 10;
}

int blk; // ~N/sqrt(Q)
vi mo(vector<pii> Q) {
	int L = 0, R = 0;
	vi s(sz(Q)), res = s;
#define K(x) pii(x.first/blk, x.second ^ -(x.first/blk & 1))
	iota(all(s), 0);
	sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
	trav(qi, s) {
		pii q = Q[qi];
		while (L > q.first) add(--L);
		while (R < q.second) add(R++);
		while (L < q.first) del(L++);
		while (R > q.second) del(--R);
		res[qi] = calc();
	}
	return res;
}

void test(int n, int q) {
	curL = curR = ops = 0;
	blk = max((int)(n / sqrt(max(q, 1))), 1);
	vector<pii> queries(q);
	trav(pa, queries) {
		pa.first = rand() % n;
		pa.second = rand() % n;
		if (pa.first > pa.second)
			swap(pa.first, pa.second);
	}
	vi res = mo(queries);
	rep(i,0,q) {
		int l = queries[i].first, r = queries[i].second;
		if (l == r) {
			assert(res[i] == -1);
		} else {
			assert(res[i] == l + (r - l) * 10);
		}
	}
	// (This inequality holds for random queries; in general it's off by a small constant)
	if (n > 100 && q > 100) {
		// cout << n << ' ' << q << ' ' << ops / (n * sqrt(q)) << endl;
		assert(ops < n * sqrt(q));
	}
}

int main() {
	srand(2);
	test(100'000, 100'000);
	test(1000, 100'000);
	test(100'000, 1000);
	rep(n,1,15) rep(q,0,n*n) {
		test(n, q);
	}
	cout << "Tests passed!" << endl;
}
