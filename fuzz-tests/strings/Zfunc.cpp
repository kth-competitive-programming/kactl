// Thanks to Ludo Pulles
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(it, v) for(auto& it : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/strings/Zfunc.h"

template <class F> void gen(string &s, int at, int alpha, F f) {
    if (at == sz(s))
        f();
    else {
        rep(i, 0, alpha) {
            s[at] = (char)('a' + i);
            gen(s, at + 1, alpha, f);
        }
    }
}

void test(const string &s) {
    int n = sz(s);
    vi found = Z(s);
    vi expected(n, 0);
    rep(i, 1, n) { // exclude index 0 (!)
        int j = 0;
        while (i + j < n && s[i + j] == s[j])
            j++;
        expected[i] = j;
    }
    assert(found == expected);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    rep(n, 0, 13) {
        string s(n, 'x');
        gen(s, 0, 3, [&]() { test(s); });
    }
    rep(n, 0, 11) {
        string s(n, 'x');
        gen(s, 0, 4, [&]() { test(s); });
    }
    cout<<"Passed"<<endl;
}