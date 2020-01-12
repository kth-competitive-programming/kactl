#include "../utilities/template.h"

#include "../../content/number-theory/Factor.h"

mt19937_64 uni(time(0));
const int ITERS=1e4;
void isValid(ull N, vector<ull> prFac){
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
    rep(n,2,1e5) {
        auto res = factor(n);
        isValid(n, res);
    }
    rep(i,2,ITERS) {
        ull n = 1 + (uni()%(1ul<<50));
        auto res = factor(n);
        isValid(n, res);
    }
    cout<<"Prime Factoring tests passed!"<<endl;
}
