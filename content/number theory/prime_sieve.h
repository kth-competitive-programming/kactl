/**
 * Author: Marcus?
 * Date:
 * Source:
 * Description:
 */
#pragma once
#include <cmath>

template<unsigned int N>
class prime_sieve {
  private:
    bool primes[N];
  public:
    prime_sieve() {
      memset(primes, 1, sizeof(primes));
      unsigned int n = (unsigned int)sqrt(N) + 1;

      for(unsigned int i = 3; i < n; i+=2) {
        if(!primes[(i - 1)/2 - 1]) continue;
        for(unsigned int j = i*i; j < N; j += i+i) {
          primes[(j - 1)/2 - 1] = false;
        }
      }
    }

    bool is_prime(int n) {
      if(n == 2) return true;
      if(n == 3) return true;
      if((n&1) == 0) return false;
      return primes[(n-1)/2 - 1];
    }
};
