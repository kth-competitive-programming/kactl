/**
 * Author:
 * Date:
 * License: CC0
 * Source:
 * Description: Multiplicative functions
 *
 * Euler's totient: $\phi(1) = 1, \phi(p) = p - 1, \phi(ip) = \phi(i)\phi(p)$
 *
 * Mobius function: $\mu(1) = 1, \mu(p) = -1, \mu(ip) = 0$
 *
 * Status: Tested
 */
#pragma once

vector<int> calcMult(int n) {
	vector<char> sieve(n);
	vector<int> phi(n), pr; phi[1] = 1; // f(1)
	rep(i, 2, n) {
		if (!sieve[i]) pr.push_back(i), phi[i] = i - 1; // f(p)
		trav(j, pr) {
			if (i * j >= n) break;
			sieve[i * j] = true;
			if (i % j == 0) { phi[i * j] = phi[i] * j; break; } // f(i*p)
			phi[i * j] = phi[i] * phi[j];
		}
	}
	return phi;
}
