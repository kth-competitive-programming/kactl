#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < int(b); ++i)
#define trav(a, v) for (auto &a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/number-theory/ModMulLL.h"

ull int128_mod_mul(ull a, ull b, ull m) { return (ull)((__uint128_t)a * b % m); }
mt19937_64 rng(1);
uniform_int_distribution<ull> uni(1, (1ull << 63) - 1);
const int ITERS = 1e7;
int main() {
    for (int i = 0; i < ITERS; i++) {
        ull c = uni(rng), a = uni(rng) % c, b = uni(rng) % c;
        ull l = int128_mod_mul(a, b, c);
        ull r = mod_mul(a, b, c);
        if (l != r) {
            cout << a << ' ' << b << ' ' << c << endl;
            cout << l << ' ' << r << endl;
        }
        assert(l == r);
    }
    cout << "Tests passed!" << endl;
}
