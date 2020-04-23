#include "../utilities/template.h"

const ll mod = 5;
ll modpow(ll a, ll e) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1);
	return e & 1 ? x * a % mod : x;
}

#define mod dummy
#define modpow dummy2
#include "../../content/number-theory/ModPow.h"
#undef mod
#undef modpow

#include "../../content/numerical/BerlekampMassey.h"

template<class F>
void gen(vector<ll>& v, int at, F f) {
	if (at == sz(v)) f();
	else {
		rep(i,0,mod) {
			v[at] = i;
			gen(v, at+1, f);
		}
	}
}

int main() {
	rep(n,1,5) {
		vector<ll> start(n);
		vector<ll> coef(n), coef2;
		vector<ll> full(2*n);
		gen(start, 0, [&]() {
		gen(coef, 0, [&]() {
			rep(i,0,n) full[i] = start[i];
			rep(i,n,2*n) full[i] = 0;
			rep(i,n,2*n) rep(j,0,n) full[i] = (full[i] + coef[j] * full[i-1 - j]) % mod;
			coef2 = berlekampMassey(full);
// rep(i,0,2*n) cerr << full[i] << ' '; cerr << endl;
// rep(i,0,n) cerr << coef[i] << ' '; cerr << endl;
// rep(i,0,sz(coef2)) cerr << coef2[i] << ' '; cerr << endl;
			if (sz(coef2) == n) assert(coef == coef2);
// rep(i,0,n) cerr << full[i] << ' ';
			rep(i,n,2*n) {
				ll x = 0;
				rep(j,0,sz(coef2)) x = (x + coef2[j] * full[i-1 - j]) % mod;
				// cerr << x << ' ';
				assert(x == full[i]);
			}
			// cerr << endl;
// cerr << endl;
		});
		});
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}

int main2() {
	vector<ll> v{0, 1, 1, 3, 5, 11};
	auto v2 = berlekampMassey(v);
	for(auto &x: v2) cout << x << ' ';
	cout << endl;
	return 0;
}
