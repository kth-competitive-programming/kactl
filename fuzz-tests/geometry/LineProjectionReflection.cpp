#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/geometry/LineProjectionReflection.h"

typedef Point<double> P;
int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    const int lim = 5;
    for (int i = 0; i < 100000; i++) {
        P p = P(rand() % lim, rand() % lim);
        P a = P(rand() % lim, rand() % lim);
        P b = P(rand() % lim, rand() % lim);
        while (a == b)
            b = P(rand() % lim, rand() % lim);
        auto proj = lineProj(a, b, p, false);
        auto refl = lineProj(a, b, p, true);
        assert(lineDist(a, b, proj) < 1e-8);
        auto manProj = (refl + p) / 2;
        assert((proj-manProj).dist() < 1e-8);
    }
}
