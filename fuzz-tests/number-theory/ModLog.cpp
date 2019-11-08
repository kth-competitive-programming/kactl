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
#include "../../content/number-theory/ModLog.h"

uniform_int_distribution<ll> uni(1, 100);
const int ITERS = 1e7;
const int LIM = 1000;
int main() {
    rep(m,1,500) {
        rep(a,1,m) {
            rep(x,0,m) {
                if (__gcd(a, m) != 1) continue;
                ull b  = mod_pow(a, x, m);
                ull res = modLog(a, b, m);
                ull recover = mod_pow(a, res, m);
                assert(recover == b);
            }
        }
    }
    cout<<"Tests passed!"<<endl;
}
