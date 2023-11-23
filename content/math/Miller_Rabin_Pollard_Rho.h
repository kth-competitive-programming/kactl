/**
 * Author:
 * Description: 
 * Usage: 
 * Time: 
 */
#pragma once

// Usage: NT::factorize(n, res);
// Caution! res may not be sorted.
mt19937 rng(1010101);
ll randInt(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}
namespace NT {
    const ll Base[12] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
    const ll NAIVE_MAX = 1'000'000'000;

    ll add(ll a, ll b, const ll mod) {
        if (a + b >= mod) return a + b - mod;
        return a + b;
    }
    ll mul(ll a, ll b, const ll mod) {
        return (__int128_t)a * b % mod;
    }
    ll _pow(ll a, ll b, const ll mod) {
        ll ret = 1;
        while (b) {
            if (b & 1) ret = mul(ret, a, mod);
            a = mul(a, a, mod); b /= 2;
        }
        return ret;
    }
    bool naive_prime(ll n) {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }
    bool is_prime(ll n) {
        if (n <= NAIVE_MAX) {
            return naive_prime(n);
        }
        if (n % 2 == 0) return false;
        // Miller-Rabin Primality test
        ll s = 0, d = n - 1;
        while (d % 2 == 0) {
            s += 1; d /= 2;
        }

        // When n < 2^64, it is okay to test only prime bases <= 37
        for (ll base : Base) {
            ll x = _pow(base, d, n), f = 0;
            if (x == 1) f = 1;
            for (int i = 0; i < s; i++) {
                if (x == n - 1) {
                    f = 1;
                }
                x = mul(x, x, n);
            }
            if (!f) return false;
        }
        return true;
    }
    ll run(ll n, ll x0, ll c) {
        function<ll(ll)> f = [c, n](ll x) {
            return NT::add(NT::mul(x, x, n), c, n);
        };
        ll x = x0, y = x0, g = 1;
        while (g == 1) {
            x = f(x);
            y = f(y); y = f(y);
            g = gcd(abs(x - y), n);
        }
        return g;
    }
    // Res is NOT sorted after this call
    void factorize(ll n, vector<ll> &Res) {
        if (n == 1) return;
        if (n % 2 == 0) {
            Res.push_back(2); factorize(n / 2, Res);
            return;
        }
        if (is_prime(n)) {
            Res.push_back(n); return;
        }
        while (1) {
            ll x0 = randInt(1, n - 1), c = randInt(1, 20) % (n - 1) + 1;
            ll g = run(n, x0, c);
            if (g != n) {
                factorize(n / g, Res); factorize(g, Res);
                return;
            }
        }
    }
};