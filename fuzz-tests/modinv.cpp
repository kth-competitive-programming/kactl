#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll M = 1e9+7, LIM = 200000;

bool isPrime(int x) {
	if (x <= 1) return false;
	for (int i = 2; i*i <= x; ++i) {
		if (x % i == 0) return false;
	}
	return true;
}

int ar[5] = {1,2,3,4,5};

int main() {
	vector<ll> inv(LIM, 1);
	for (int M = 1; M <= 1000; ++M) {
		if (!isPrime(M)) continue;
		inv.assign(LIM, 123123);
		inv[0] = -1000;
		inv[1] = 1;
		rep(i,2,LIM)
			inv[i] = M - (M / i) * inv[M % i] % M;
		rep(i,0,M) {
			bool works = (i * inv[i] % M == 1);
			bool relp = (__gcd(i, M) == 1);
			assert(works == relp);
		}
	}
}

ll inv[LIM] = {-10000, 1};
int main2() {
	rep(i,2,LIM) inv[i] = M - (M / i) * inv[M % i] % M;
	cout << inv[0] << ' ' << inv[1] << ' ' << inv[2] << ' ' << inv[3] << endl;
	return 0;
}
