#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < int(b); ++i)
#define trav(a, v) for (auto &a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/number-theory/ModLog.h"

int main() {
    const int lim = 100;
    rep(m,1,lim) {
        rep(a,0,lim) {
            if (__gcd(a, m) != 1) continue;
            vector<ll> ans(m, -1);
            ll b = 1 % m;
            rep(x,0,m) {
                if (ans[b] == -1) ans[b] = x;
                b = b * a % m;
            }
            rep(b,0,lim) {
                ll res = modLog(a, b, m);
                ll b2 = b % m;
                if (ans[b2] == -1) assert(res == LLONG_MAX);
                else {
                    if (ans[b2] != res) {
                        cerr << "FAIL" << endl;
                        cerr << "Expected log(" << a << ", " << b << ", " << m << ") = " << ans[b2] << ", found " << res << endl;
                        return 1;
                    }
                }
            }
        }
    }
    cout<<"Tests passed!"<<endl;
}
