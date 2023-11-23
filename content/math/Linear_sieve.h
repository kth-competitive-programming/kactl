/**
 * Author:
 * Description: 
 * Usage: 
 * Time: 
 */
#pragma once

void linear_sieve() {
    vector<int> p(M), pr;
    vector<int> mu(M), phi(M);
    for (int i = 2; i < M; i++) {
        if (!p[i]) {
            pr.push_back(i);
            mu[i] = -1;
            phi[i] = i - 1; // value of multiplicative function for prime
        }
        for (int j = 0; j < pr.size() && i * pr[j] < M; j++) {
            p[i * pr[j]] = 1;
            if (i % pr[j] == 0) {
                mu[i * pr[j]] = 0;
                phi[i * pr[j]] = phi[i] * pr[j];
                break;
            }
            else {
                mu[i * pr[j]] = mu[i] * mu[pr[j]];
                phi[i * pr[j]] = phi[i] * phi[pr[j]];
            }
        }
    }
    for (int i = 2; i < 50; i++) {
        cout << "mu(" << i << ") = " << mu[i] << ' ';
        cout << "phi(" << i << ") = " << phi[i] << '\n';
    }
}