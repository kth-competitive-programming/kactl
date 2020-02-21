#include "../utilities/template.h"

#include "../../content/number-theory/ModSum.h"

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
						assert(false);
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
						assert(false);
					}
				}
			}
		}
	}
}

int main() {
	compare(); compare2();
	assert(modsum((ll)1e18, 1, 2, 3) == (ll)1e18);
	rep(i,0,50) {
		ll t = (ll)rand() << 3;
		ll c = (ll)rand() << 2;
		ll k = (ll)rand() << 2;
		ll m = (ll)rand() >> 2;
		assert(abs(modsum(t, c, k, m) / ((long double)m/2 * t) - 1)<1e-5);
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}
