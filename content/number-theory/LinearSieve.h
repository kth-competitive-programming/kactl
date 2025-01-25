/**
 * Author: Unknown
 * Source: https://cp-algorithms.com/algebra/prime-sieve-linear.html
 * Description: Finds smallest prime factor of each integer
 * Time: $O(N)$
 * Status: Tested
 */
#pragma once

const int LIM = 1000000;
vi lp(LIM+1), primes;

rep(i, 2, LIM + 1) {
	if (lp[i] == 0) primes.push_back(lp[i] = i);
	for (int j = 0; j < sz(primes) && i * primes[j] <= LIM && primes[j] <= lp[i]; ++j) 
		lp[i * primes[j]] = primes[j];
}
