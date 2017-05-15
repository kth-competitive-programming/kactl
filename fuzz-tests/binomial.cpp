#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/combinatorial/RollingBinomial.h"

ll modpow(ll a, ll e) {
	if (!e) return 1;
	ll x = modpow(a, e >> 1);
	x = x * x % mod;
	if (e & 1) x = x * a % mod;
	return x;
}

ll choose(int n, int k) {
	if(k>n || k<0) return 0;
	k = min(k, n-k);
	ll c = 1;
	for(int i = 1; i <= k; ++i)
		c = c * (n - i + 1) % mod * invs[i] % mod;
	return c;
}

int main() {
	int maxn = 100000;
	invs.resize(maxn+1);
	rep(i,0,maxn+1) invs[i] = modpow(i,mod-2);
	Bin bi;
	rep(it,0,1000000) {
		int a = (rand() % 100) - 20, b = (rand() % 100) - 20;
		ll r = bi.choose(a, b);
		ll r2 = choose(a, b);
		assert(r == r2);
	}
	rep(it,0,1000000) {
		int a = (rand() % 100) - 20, b = (rand() % 100) - 20;
		ll r = bi.choose(a, b);
		ll r2 = choose(a, b);
		assert(r == r2);
	}
}
