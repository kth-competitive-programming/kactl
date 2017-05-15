#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/number-theory/ModSum.h"

ll rmod(ll x, ll m) {
	x %= m;
	return x < 0 ? x + m : x;
}

ll rdiv(ll x, ll y) {
	x -= rmod(x, y);
	return x / y;
}

ll modsum_naive(ll to, ll c, ll k, ll m) {
	ll res = 0;
	for (int i = 0; i < (int)to; ++i)
		res += rmod(c + k * i, m);
	return res;
}

ll divsum_naive(ll to, ll c, ll k, ll m) {
	ll res = 0;
	for (int i = 0; i < (int)to; ++i)
		res += rdiv(c + k * i, m);
	return res;
}

void compare() {
	rep(to,0,30) {
		rep(c,-30,30) {
			rep(k,-30,30) {
				rep(m,1,30) {
					ll a = modsum(to, c, k, m);
					ll b = modsum_naive(to, c, k, m);
					if (a != b) {
						cout << "differ! " << to << ' ' << c << ' ' << k << ' ' << m << ": " << a << " vs " << b << endl;
						return;
					}
				}
			}
		}
	}
}

void compare2() {
	rep(to,0,30) {
		rep(c,0,30) {
			rep(k,0,30) {
				rep(m,1,30) {
					ll a = divsum(to, c, k, m);
					ll b = divsum_naive(to, c, k, m);
					if (a != b) {
						cout << "differ! " << to << ' ' << c << ' ' << k << ' ' << m << ": " << a << " vs " << b << endl;
						return;
					}
				}
			}
		}
	}
}

int main() {
	compare(); compare2();
	cout << modsum((ll)1e18, 1, 2, 3) << endl;
	cout << (ll)1e18 << endl;
	rep(i,0,50) {
		ll t = (ll)rand() << 3;
		ll c = (ll)rand() << 2;
		ll k = (ll)rand() << 2;
		ll m = (ll)rand() >> 2;
		cout << modsum(t, c, k, m) / (long double)(m/2 * t) << endl;
	}
	cout << modsum(1000000000000000000LL, 11231, 102917231231LL, 1236712312LL) << endl;
	// rep(i,0,1000000) {
		// modsum(1000000000000000000LL, 11231, 102917231231LL, 1236712312LL);
	// }
	return 0;
}
