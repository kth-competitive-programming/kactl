/**
 * Author: Jakob Kogler, chilli, pajenegod
 * Date: 2020-04-12
 * License: CC0
 * Source:
 * Description: Prime sieve for generating all primes up to LIM.
 * Status: Stress-tested
 * Time: LIM=1e9 $\approx$ 1.5s
 * Details: Despite its n log log n complexity, segmented sieve is still faster
 * than other options, including bitset sieves and linear sieves. This is
 * primarily due to its low memory usage, which reduces cache misses. This
 * implementation skips even numbers.
 *
 * Benchmark can be found here: https://ideone.com/e7TbX4
 */
#pragma once

const int LIM = 1e6;
vi eratosthenes() {
	const int S = round(sqrt(LIM)), h = (LIM - 1) / 2;
	vi pr({2}), sieve(S + 1);
	vector<array<int, 2>> cp;
	for (int i = 3; i < S; i += 2) {
		if (sieve[i]) continue;
		cp.push_back({i, i * i / 2 - 1});
		for (int j = i * i; j <= S; j += 2 * i) sieve[j] = true;
	}
	for (int l = 1; l <= h; l += S) {
		array<bool, S> block{};
		trav(i, cp) {
			int idx = i[1];
			for (; idx < S; idx += i[0]) block[idx] = true;
			i[1] = idx - S;
		}
		rep(i,0,min(S, h - l))
			if (!block[i]) pr.push_back((l + i) * 2 + 1);
	};
	return pr;
}
