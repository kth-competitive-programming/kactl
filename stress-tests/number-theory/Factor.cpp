#include "../utilities/template.h"

#include "../../content/number-theory/Factor.h"

mt19937_64 uni(time(0));
const int ITERS=1e4;
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
    assert((factor(2299) == vector<ull>{11, 19, 11}));
    rep(n,2,1e5) {
        auto res = factor(n);
        assertValid(n, res);
        res = factor(n*ll(n));
        assertValid(n*ll(n), res);
    }
    rep(i,2,ITERS) {
        ull n = 1 + (uni()%(1ul<<63));
        auto res = factor(n);
        assertValid(n, res);
    }
    cout<<"Prime Factoring tests passed!"<<endl;
}
