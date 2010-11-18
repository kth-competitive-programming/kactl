/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-16
 * Source: Basic algorithm knowledge
 * Description: An implementation of Eratosthenes sieve optimized for shortness and not for speed. After calling calculatePrimes(N) $isPrime[i]=true$ ($0\leq i < N$) if and only if $i$ is prime. primes will be an ordered vector containing all primes less than N. If the list of primes is not needed the three lines containing the vector primes can be removed.
 * Time: $O(N\log(N)\log(\log(N)))$
 * Memory: O(N)
 * Status: Tested with UVa problem 10015 - Joseph's Cousin
 * Usage:
calculatePrimes(1000000)
if (isPrime[999997]) cout << primes.back();
 */
#pragma once

#include <vector>
using namespace std;

vector<bool> isPrime;
vector<int> primes;

void calculatePrimes(int N) {
	isPrime = vector<bool>(N,true);
	isPrime[0] = isPrime[1] = false;
	primes.clear();
	rep(i,2,N) {
		if (isPrime[i]) {
			primes.push_back(i);
			rep(j,i,(N-1)/i+1) isPrime[i*j] = false;
		}
	}
}
