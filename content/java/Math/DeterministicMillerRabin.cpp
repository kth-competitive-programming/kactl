/*
** Deterministic Miller-Rabin
** if n < 3,825,123,056,546,413,051, it is enough to test
** a = 2, 3, 5, 7, 11, 13, 17, 19, and 23.
*/
/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Deterministic Miller-Rabin.
 *  if n < 3,825,123,056,546,413,051, it is enough to test
 *  a = 2, 3, 5, 7, 11, 13, 17, 19, and 23.
 */
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

vector<ll> mr_values({2, 3, 5, 7, 11, 13, 17, 19, 23});

ll mulmod(ll a, ll b, ll n) {
  ll erg = 0;
  ll r = 0;
  while (b > 0) {
    // unsigned long long gives enough room
    // for base 10 operations
    ll x = ((a % n) * (b % 10)) % n;
    for (ll i = 0; i < r; i++) x = (x * 10) % n;
    erg = (erg + x) % n;
    r++;
    b /= 10;
  }
  return erg;
}

ll fastexp(ll a, ll b, ll n) {
  if (b == 0) return 1;
  if (b == 1) return a % n;
  ll res = 1;
  while (b > 0) {
    if (b % 2 == 1) res = mulmod(a, res, n);
    a = mulmod(a, a, n);
    b /= 2;
  }
  return res;
}

bool mrtest(ll n) {
  if (n == 1) return false;
  ll d = n - 1;
  ll s = 0;
  while (d % 2 == 0) {
    s++;
    d /= 2;
  }
  for (ll j = 0; j < (ll)mr_values.size(); j++) {
    if (mr_values[j] > n - 1) continue;
    ll ad = fastexp(mr_values[j], d, n);
    if (ad % n == 1) continue;
    bool notcomp = false;
    for (ll r = 0; r <= max(0ull, s - 1); r++) {
      ll rr = fastexp(2, r, n);
      ll ard = fastexp(ad, rr, n);
      if (ard % n == n - 1) {
        notcomp = true;
        break;
      }
    }
    if (!notcomp) return false;
  }
  return true;
}

bool isprime(ll n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;
  return mrtest(n);
}
