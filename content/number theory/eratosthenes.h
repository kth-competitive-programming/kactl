/**
 * Author: Håkan Terelius
 * Date: 2009-08-26
 * Source: http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * Description: Prime sieve for generating all primes up to a certain limit. isprime$[i]$ is true iff $i$ is a prime. prime[] contains all primes up to LIMIT, in total $primes$ numbers.
 * Status: Tested
 * Time: LIMIT=5'000'000 $\approx$ 0.1 s
 */
#pragma once
#include <cstring>

const int MAX_PR = 5000000;
bool isprime[MAX_PR];
vector<int> eratosthenes_sieve(int LIMIT) {
	memset(isprime, 1, sizeof(isprime));
	isprime[0]=isprime[1]=false;
	for(int i=2;i*i<LIMIT;++i)
		if(isprime[i])
			for(int j=i*i;j<LIMIT;j+=i)
				isprime[j]=false;
	vector<int> pr;
	for(int i=2;i<LIMIT;++i)
		if(isprime[i])
			pr.push_back(i);
	return pr;
}
