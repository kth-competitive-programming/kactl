#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll M = 1e9+7;
ll LIM = 200000;

bool isPrime(int x) {
	if (x <= 1) return false;
	for (int i = 2; i*i <= x; ++i) {
		if (x % i == 0) return false;
	}
	return true;
}

int ar[5] = {1,2,3,4,5};

int main() {
	// vector<ll> inv(LIM, 1);

	for (int M = 1; M <= 1000; ++M) {
		#define mod=1000000007 /**/
		#define ll /**/
		#include "../../content/number-theory/ModInverse.h"
		#undef mod
		#undef ll
		if (!isPrime(M)) continue;
		rep(i,0,M) {
			bool works = (i * inv[i] % M == 1);
			bool relp = (__gcd(i, M) == 1);
			assert(works == relp);
		}
	}
	cout<<"Tests pass!"<<endl;
}

