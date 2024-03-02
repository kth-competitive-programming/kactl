#include "../utilities/template.h"

// #include "../../content/data-structures/MoQueries.h"

ll curL = 0, curR = 0, ops = 0;
void add(ll ind, ll end) {
	if (curL != curR) {
		if (end == 0) assert(ind == curL - 1);
		else assert(ind == curR);
	}
	if (curL == curR) curL = ind, curR = ind + 1;
	else if (ind == curR) curR++;
	else curL--;
	ops++;
}
void del(ll ind, ll end) {
	if (end == 0) assert(ind == curL);
	else assert(ind == curR - 1);
	if (ind == curR - 1) curR--;
	else curL++;
	assert(curL <= curR);
	ops++;
}

ll calc() {
	return curL == curR ? -1 : curL + (curR - curL) * 10;
}

ll blk; // ~N/sqrt(Q)
vi mo(vector<pii> Q) {
	ll L = 0, R = 0;
	vi s(sz(Q)), res = s;
#define K(x) pii(x.first/blk, x.second ^ -(x.first/blk & 1))
	iota(all(s), 0);
	sort(all(s), [&](ll s, ll t){ return K(Q[s]) < K(Q[t]); });
	for (ll qi : s) {
		pii q = Q[qi];
		while (L > q.first) add(--L, 0);
		while (R < q.second) add(R++, 1);
		while (L < q.first) del(L++, 0);
		while (R > q.second) del(--R, 1);
		res[qi] = calc();
	}
	return res;
}

void test(ll n, ll q) {
	curL = curR = ops = 0;
	blk = max((ll)(n / sqrt(max(q, 1ll))), 1ll);
	vector<pii> queries(q);
	for (auto& pa : queries) {
		pa.first = rand() % n;
		pa.second = rand() % n;
		if (pa.first > pa.second)
			swap(pa.first, pa.second);
	}
	vi res = mo(queries);
	rep(i,0,q) {
		ll l = queries[i].first, r = queries[i].second;
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

#undef K

namespace MoTree {

vi vals;
ll sum;
deque<ll> path;
void add(ll i, ll end) {
	sum += vals[i];
	ops++;
	if (end == 0) path.push_front(i);
	else path.push_back(i);
}
void del(ll i, ll end) {
	sum -= vals[i];
	ops++;
	assert(!path.empty());
	if (end == 0) {
		assert(path.front() == i);
		path.pop_front();
	} else {
		assert(path.back() == i);
		path.pop_back();
	}
}
ll calc() { return sum; }

vi moTree(vector<array<ll, 2>> Q, vector<vi>& ed, ll root=0){
	ll N = sz(ed), pos[2] = {};
	vi s(sz(Q)), res = s, I(N), L(N), R(N), in(N), par(N);
	add(0, 0), in[0] = 1;
	auto dfs = [&](ll x, ll p, ll dep, auto& f) -> void {
		par[x] = p;
		L[x] = N;
		if (dep) I[x] = N++;
		for (ll y : ed[x]) if (y != p) f(y, x, !dep, f);
		if (!dep) I[x] = N++;
		R[x] = N;
	};
	dfs(root, -1, 0, dfs);
#define K(x) pii(I[x[0]] / blk, I[x[1]] ^ -(I[x[0]] / blk & 1))
	iota(all(s), 0);
	sort(all(s), [&](ll s, ll t){ return K(Q[s]) < K(Q[t]); });
	for (ll qi : s) rep(end,0,2) {
		ll &a = pos[end], b = Q[qi][end], i = 0;
#define step(c) { if (in[c]) del(a, end), in[a] = 0; \
                  else add(c, end), in[c] = 1; a = c; }
		while (!(L[b] <= L[a] && R[a] <= R[b]))
			I[i++] = b, b = par[b];
		while (a != b) step(par[a]);
		while (i--) step(I[i]);
		if (end) res[qi] = calc();
	}
	return res;
}

}

void testTr(ll n, ll q) {
	ops = 0;
	blk = max((ll)(n / sqrt(max(q, 1ll))), 1ll);
	vector<array<ll, 2>> queries(q);
	for (auto& pa : queries) {
		pa[0] = rand() % n;
		pa[1] = rand() % n;
	}
	vi par(n), val(n);
	rep(i,1,n) par[i] = rand() % i;
	rep(i,0,n) val[i] = rand() % 1000;
	vector<vi> ed(n);
	rep(i,1,n) ed[par[i]].push_back(i), ed[i].push_back(par[i]);
	MoTree::vals = val;
	MoTree::sum = 0;
	MoTree::path.clear();
	vi res = MoTree::moTree(queries, ed);
	vi seen(n);
	rep(i,0,q) {
		// Tree depth is logarithmic, so compute query answers naively
		ll l = queries[i][0], r = queries[i][1];
		ll at = l;
		while (at != 0) seen[at] = 1, at = par[at];
		seen[at] = 1;
		ll sum = 0;
		while (!seen[r]) sum += val[r], r = par[r];
		at = l;
		while (at != 0) seen[at] = 0, at = par[at];
		seen[at] = 0;
		while (l != r) sum += val[l], l = par[l];
		sum += val[l];
		assert(res[i] == sum);
	}
}

int main() {
	srand(2);
	rep(it,0,10) rep(n,1,15) rep(q,0,n*n) {
		testTr(n, q);
	}
	testTr(100'000, 100'000);
	testTr(1000, 100'000);
	testTr(100'000, 1000);
	test(100'000, 100'000);
	test(1000, 100'000);
	test(100'000, 1000);
	rep(it,0,10) rep(n,1,15) rep(q,0,n*n) {
		test(n, q);
	}
	cout << "Tests passed!" << endl;
}
