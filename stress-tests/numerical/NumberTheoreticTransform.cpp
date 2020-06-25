#include "../utilities/template.h"

typedef vector<ll> vl;
namespace ignore {
#include "../../content/number-theory/ModPow.h"
}
ll modpow(ll a, ll e);
#include "../../content/numerical/NumberTheoreticTransform.h"
ll modpow(ll a, ll e) {
    if (e == 0)
        return 1;
    ll x = modpow(a * a % mod, e >> 1);
    return e & 1 ? x * a % mod : x;
}

vl simpleConv(vl a, vl b) {
	int s = sz(a) + sz(b) - 1;
	if (a.empty() || b.empty()) return {};
	vl c(s);
	rep(i,0,sz(a)) rep(j,0,sz(b))
		c[i+j] = (c[i+j] + (ll)a[i] * b[j]) % mod;
	for(auto &x: c) if (x < 0) x += mod;
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
	ll res = 0, res2 = 0;
	int ind = 0, ind2 = 0;
	vl a, b;
	rep(it,0,6000) {
		a.resize(ra() % 10);
		b.resize(ra() % 10);
		for(auto &x: a) x = (ra() % 100 - 50+mod)%mod;
		for(auto &x: b) x = (ra() % 100 - 50+mod)%mod;
		for(auto &x: simpleConv(a, b)) res += (ll)x * ind++ % mod;
		for(auto &x: conv(a, b)) res2 += (ll)x * ind2++ % mod;
		a.resize(16);
        vl a2 = a;
        ntt(a2);
        rep(k, 0, sz(a2)) {
            ll sum = 0;
            rep(x, 0, sz(a2)) { sum = (sum + a[x] * modpow(root, k * x * (mod - 1) / sz(a))) % mod; }
            assert(sum == a2[k]);
        }
	}
	assert(res==res2);
	cout<<"Tests passed!"<<endl;
}
