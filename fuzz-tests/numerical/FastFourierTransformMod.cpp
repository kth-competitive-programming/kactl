#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll mod = 1000000007;

#include "../../content/numerical/FastFourierTransformMod.h"

vl simpleConv(vl a, vl b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1;
	vl c(s);
	rep(i,0,sz(a)) rep(j,0,sz(b))
		c[i+j] = (c[i+j] + (ll)a[i] * b[j]) % mod;
	trav(x, c) if (x < 0) x += mod;
	return c;
}

int ra() {
	static unsigned X;
	X *= 123671231;
	X += 1238713;
	X ^= 1237618;
	return (X >> 1);
}

int main() {
	vl a, b;
	rep(it,0,6000) {
		a.resize(ra() % 100);
		b.resize(ra() % 100);
		trav(x, a) x = ra() % mod;
		trav(x, b) x = ra() % mod;
		auto v1 = simpleConv(a, b);
		auto v2 = convMod<mod>(a, b);
		assert(v1 == v2);
	}
	cout<<"Tests passed!"<<endl;
}
