#include "../utilities/template.h"

#include "../../content/number-theory/MillerRabin.h"
#include "../../content/number-theory/eratosthenes.h"

ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
int afactors[] = {2, 3, 5, 13, 19, 73, 193, 407521, 299210837};

bool oldIsPrime(ull p) {
	if (p == 2) return true;
	if (p == 1 || p % 2 == 0) return false;
	ull s = p - 1;
	while (s % 2 == 0) s /= 2;
	rep(i,0,15) {
		ull a = rand() % (p - 1) + 1, tmp = s;
		ull mod = mod_pow(a, tmp, p);
		while (tmp != p - 1 && mod != 1 && mod != p - 1) {
			mod = mod_mul(mod, mod, p);
			tmp *= 2;
		}
		if (mod != p - 1 && tmp % 2 == 0) return false;
	}
	return true;
}

void rec(ull div, ll num, int ind, int factors) {
	if (ind == sizeof(afactors)/sizeof(*afactors)) {
		if (factors == 1) assert(isPrime(div));
		if (factors > 1) assert(!isPrime(div));
		return;
	}
	for (;;) {
		rec(div, num, ind+1, factors);
		div *= afactors[ind];
		if (num % div != 0) break;
		factors++;
	}
}

int main() {
	eratosthenes_sieve(MAX_PR);
	trav(a, A) rec(1, a, 0, 0);

	rep(n,0,MAX_PR) {
		if (isPrime(n) != isprime[n]) {
			cout << "fails for " << n << endl;
			return 1;
		}
	}

	ull n = 1;
	rep(i,0,1000000) {
		n ^= (ull)rand();
		n *= 1237618231ULL;
		if (oldIsPrime(n) != isPrime(n)) {
			cout << "differs from old for " << n << endl;
			assert(false);
		}
	}
	cout << "Tests passed!" << endl;
}
