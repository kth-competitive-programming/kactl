#include "../utilities/template.h"

#include "../../content/number-theory/Factor.h"

mt19937_64 uni(time(0));
void assertValid(ull N, vector<ull> prFac){
    ull cur=1;
    for (auto i: prFac){
        if (!isPrime(i)){
            cout<<N<<endl;
            cout<<i<<endl;
            assert(isPrime(i));
        }
        cur *= i;
    }
    if (cur!= N)
        cout<<cur<<' '<<N<<endl;
    assert(cur == N);
}
int main() {
    assert(factor(1).empty());
    assert(factor(2) == vector<ull>{2});
    {
      auto res = factor(2299);
      sort(all(res));
      assert(res == vector<ull>({11, 11, 19}));
    }
    rep(n,2,1e5) {
        auto res = factor(n);
        assertValid(n, res);
        res = factor(n*ll(n));
        assertValid(n*ll(n), res);
    }
    rep(i,2,1e5) {
        ull n = 1 + (uni()%(3ul<<61));
        auto res = factor(n);
        assertValid(n, res);
    }
    cout<<"Tests passed!"<<endl;
}
