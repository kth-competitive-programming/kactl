#include "../utilities/template.h"

ll modpow(ll a, ll e, ll mod) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1, mod);
	return e & 1 ? x * a % mod : x;
}
bool isPrime(int x) {
	if (x <= 1) return false;
	for (int i = 2; i*i <= x; ++i) {
		if (x % i == 0) return false;
	}
	return true;
}
int main() {
	rep(it,1,1000) {
		int mod = it, LIM=1000;
		if (!isPrime(mod)) continue;
		#include "../../content/number-theory/ModInverse.h"
		for (int i=1; i<it; i++){
			assert(inv[i] == modpow(i, mod-2, mod));
		}
	}
	cout<<"Tests pass!"<<endl;
}

