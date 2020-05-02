#include "../utilities/template.h"

#include "../../content/number-theory/ModMulLL.h"

const int ITERS = 5'000'000; // (not really enough to say much, need >1e10 for any kind of certainty)

ull int128_modmul(ull a, ull b, ull m) { return (ull)((__uint128_t)a * b % m); }

void test(ull lim, bool expectSuccess) {
	mt19937_64 rng(1);
	uniform_int_distribution<ull> uni(1, lim);
	uniform_int_distribution<ull> uniSmall(0, lim / 10000);

	for (int i = 0;; i++) {
		if (expectSuccess && i >= ITERS) break;
		// if (i % 1'000'000 == 0) cerr << '.' << flush;
		ull c = i&1 ? lim - uniSmall(rng) : uni(rng);
		ull a = i&2 ? c - uniSmall(rng) : i&4 ? (1ULL << 62) - uniSmall(rng) : uni(rng);
		ull b = i&8 ? c - uniSmall(rng) : uni(rng);
		if (a > c || b > c) continue;
		ull l = int128_modmul(a, b, c);
		ull r = modmul(a, b, c);
		if (l != r) {
			if (!expectSuccess) break;
			cout << a << ' ' << b << ' ' << c << endl;
			cout << l << ' ' << r << endl;
			abort();
		}
	}
}

int main() {
	const ull lim = 7268172458553106874ULL; // floor((sqrt(177) - 7) / 16 * 2**64)
	test(lim, true);
	test((ull)(lim * 1.01L), false);
	// test((ull)(lim * 1.001L), false);
	cout << "Tests passed!" << endl;
}
