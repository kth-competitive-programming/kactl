#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
#include "../utilities/template.h"

#include "../../content/number-theory/Factor.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  cin >> q;
  while(q--) {
    ull val;
    cin >> val;
    vector<ull> factors = factor(val);
    sort(all(factors));
    cout << sz(factors) << ' ';
    for(ull fac : factors)
      cout << fac << " ";
    cout << '\n';
  }
}
