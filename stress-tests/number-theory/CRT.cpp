#include "../utilities/template.h"

#include "../../content/number-theory/CRT.h"

ll rmod(ll a, ll b) { return (a % b + b) % b; }

std::mt19937_64 rng(2);

ll randExp() {
	int e = rand() % 63; // 64
	return uniform_int_distribution<ll>(0, (ll)((1ULL << e) - 1))(rng);
}

int main(int argc, char** argv) {
	rep(it,0,10000000) {
		ll a = randExp() * (rand() % 2 ? 1 : -1);
		ll b = randExp() * (rand() % 2 ? 1 : -1);
		ll m = randExp() + 1;
		ll n = randExp() + 1;
		ll g = __gcd(m, n);
		if (n * (__int128_t)m > LLONG_MAX) continue;
		if (n * (__int128_t)m > (1LL << 62) && (abs(a) > m || abs(b) > n)) continue;
		if ((a - b) % g == 0) {
			ll r = crt(a, m, b, n);
			if (rmod(r, m) != rmod(a, m) || rmod(r, n) != rmod(b, n)) {
				cout << a << endl;
				cout << b << endl;
				cout << m << endl;
				cout << n << endl;
			}
			assert(rmod(r, m) == rmod(a, m));
			assert(rmod(r, n) == rmod(b, n));
			if (-m < a && a < m && -n < b && b < n) {
				assert(0 <= r);
				assert(r < m*n/g);
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
