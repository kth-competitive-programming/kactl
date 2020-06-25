#include "../utilities/template.h"

#include "../../content/number-theory/MillerRabin.h"
namespace sieve {
#include "../../content/number-theory/FastEratosthenes.h"
}

ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
int afactors[] = {2, 3, 5, 13, 19, 73, 193, 407521, 299210837};

const ull MR_LIM = 1ULL << 62;

// Accurate for arbitrary 64-bit numbers
ull int128_mod_mul(ull a, ull b, ull m) { return (ull)((__uint128_t)a * b % m); }
ull int128_mod_pow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = int128_mod_mul(b, b, mod), e /= 2)
		if (e & 1) ans = int128_mod_mul(ans, b, mod);
	return ans;
}
bool oldIsPrime(ull p) {
	if (p == 2) return true;
	if (p == 1 || p % 2 == 0) return false;
	ull s = p - 1;
	while (s % 2 == 0) s /= 2;
	rep(i,0,15) {
		ull a = rand() % (p - 1) + 1, tmp = s;
		ull mod = int128_mod_pow(a, tmp, p);
		while (tmp != p - 1 && mod != 1 && mod != p - 1) {
			mod = int128_mod_mul(mod, mod, p);
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

const int MAXPR = 1e6;
int main() {
	auto prs = sieve::eratosthenes();
	vector<bool> isprime(MAXPR);
	for (auto i: prs) isprime[i] = true;
	for(auto &a: A) rec(1, a, 0, 0);

	rep(n,0,MAXPR) {
		if (isPrime(n) != isprime[n]) {
			cout << "fails for " << n << endl;
			return 1;
		}
	}

	ull n = 1;
	rep(i,0,1000000) {
		n ^= (ull)rand();
		n *= 1237618231ULL;
		if (n < MR_LIM && oldIsPrime(n) != isPrime(n)) {
			cout << "differs from old for " << n << endl;
			cout << "old says " << oldIsPrime(n) << endl;
			cout << "new says " << isPrime(n) << endl;
			assert(false);
		}
	}
	cout << "Tests passed!" << endl;
}
