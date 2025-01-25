/**
 * Author: Tyler Marks
 * Description: Gets all factors of a number $N$ given the prime factorization of the number.
 * Time: $O(\sqrt[3]{N})$
 * Status: Tested
 */

void getFactors(auto &primes, auto &pows, auto &factors, int i = 0, ll n = 1) {
	if(i == sz(primes)) return void(factors.push_back(n));
	for(ll j = 0, pow = 1; j <= pows[i]; j++, pow *= primes[i])
		getFactors(primes, pows, factors, i+1, n * pow);
}
