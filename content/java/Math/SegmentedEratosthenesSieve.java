/**
 * Author: e-maxx -> Musin
 * Date: 2019-11-26
 * Source: e-maxx
 * Description: Prime sieve for generating all primes up to a certain limit.
 * Time: $O(n \log n)$
 */
class SegmentedEratosthenesSieve {
  int BLOCK_SIZE = 10000;  //1e4..1e5 is the best

  int sieve(int n) {
    int nsqrt = (int) sqrt(n + .1);
    boolean[] isPrime = new boolean[nsqrt + 1];
    fill(isPrime, true);
    int[] primes = new int[nsqrt + 1];
    int cnt = 0;
    for (int i = 2; i <= nsqrt; i++) {
      if (isPrime[i]) {
        primes[cnt++] = i;
        if (i * (long) i <= nsqrt)
          for (int j = i * i; j <= nsqrt; j += i)
            isPrime[j] = false;
      }
    }
    int result = 0;
    boolean[] block = new boolean[BLOCK_SIZE];
    for (int k = 0; k <= n / BLOCK_SIZE; k++) {
      fill(block, true);
      int start = k * BLOCK_SIZE;
      for (int i = 0; i < cnt; i++) {
        int startIdx = (start + primes[i] - 1) / primes[i];
        int j = max(startIdx, 2) * primes[i] - start;
        for (; j < BLOCK_SIZE; j += primes[i])
          block[j] = false;
      }
      if (k == 0)
        block[0] = block[1] = false;
      for (int i = 0; i < BLOCK_SIZE && start + i <= n; i++)
        if (block[i])
          result++;
    }
    return result;
  }
}
