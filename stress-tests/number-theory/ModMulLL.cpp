#include "../utilities/template.h"

#include "../../content/number-theory/ModMulLL.h"

const int ITERS = 5'000'000; // (not really enough to say much, need >1e10 for any kind of certainty)

ull double_modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1. / (double)M * (double)a * (double)b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ull int128_modmul(ull a, ull b, ull m) { return (ull)((__uint128_t)a * b % m); }

void test(ull lim, bool expectSuccess, bool useDoubles) {
	mt19937_64 rng(1);
	uniform_int_distribution<ull> uni(1, lim);
	uniform_int_distribution<ull> uniSmall(0, lim / 10000);

	int it = 0;
	for (int i = 0;; i++) {
		// if (i % 1'000'000 == 0) cerr << '.' << flush;
		ull c = i&1 ? lim - uniSmall(rng) : uni(rng);
		ull a = i&2 ? c - uniSmall(rng) : i&4 && !useDoubles ? (1ULL << 62) - uniSmall(rng) : uni(rng);
		ull b = i&8 ? c - uniSmall(rng) : uni(rng);
		if (a > c || b > c) continue;
		if (expectSuccess && it++ >= ITERS) break;
		ull l = int128_modmul(a, b, c);
		ull r = useDoubles ? double_modmul(a, b, c) : modmul(a, b, c);
		if (l != r) {
			if (!expectSuccess) break;
			cout << a << ' ' << b << ' ' << c << endl;
			cout << l << ' ' << r << endl;
			abort();
		}
	}
}

void testSq(ull lim, bool expectSuccess, bool useDoubles) {
	// Test that modmul works for squaring slightly beyond the stated bounds.
	// Factor.h relies on this (and has a proof sketch in the doc comment).
	mt19937_64 rng(1);
	uniform_int_distribution<ull> uni(1, lim);
	uniform_int_distribution<ull> uniSmall(0, lim / 10000);
	uniform_int_distribution<ull> uniTiny(0, (int)(sqrt(lim) / 2));

	for (int i = 0;; i++) {
		if (expectSuccess && i >= ITERS) break;
		// if (i % 1'000'000 == 0) cerr << '.' << flush;
		ull c = i&1 ? lim - uniSmall(rng) : uni(rng);
		ull a = expectSuccess ? c + uniTiny(rng) : c + uniSmall(rng);
		ull l = int128_modmul(a, a, c);
		ull r = useDoubles ? double_modmul(a, a, c) : modmul(a, a, c);
		if (l != r) {
			if (!expectSuccess) break;
			cout << a << ' ' << c << endl;
			cout << l << ' ' << r << endl;
			abort();
		}
	}
}

int main() {
	const ull limDoubles = 1ULL << 52;
	test(limDoubles, true, true);
	test((ull)(limDoubles * 1.02L), false, true);

	testSq(limDoubles, true, true);

	const ull lim = 7268172458553106874ULL; // floor((sqrt(177) - 7) / 16 * 2**64)
	test(lim, true, false);
	test((ull)(lim * 1.01L), false, false);
	// test((ull)(lim * 1.001L), false, false);

	testSq(lim, true, false);
	testSq(lim, false, false);
	cout << "Tests passed!" << endl;
}
