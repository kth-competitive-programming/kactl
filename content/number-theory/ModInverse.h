/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * Source: Russian page
 * Description: Pre-computation of modular inverses. Assumes LIM $\le$ M and that M is a prime.
 * Status: Works
 */

const ll M = 1e9+7, LIM = 200000;
ll inv[LIM] = {1e5, 1};
rep(i,2,LIM) inv[i] = M - (M / i) * inv[M % i] % M;
