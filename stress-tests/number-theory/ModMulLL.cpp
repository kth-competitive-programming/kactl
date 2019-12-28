#include "../utilities/template.h"

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
