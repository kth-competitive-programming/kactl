#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

#include "../../content/geometry/Point.h"
#include "../../content/geometry/lineRefl.h"
typedef Point<double> P;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout<<refl(P(0, 0), P(0, 4), P(-5,0))<<endl;
}