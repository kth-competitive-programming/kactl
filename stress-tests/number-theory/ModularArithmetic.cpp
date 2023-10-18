#include "../utilities/template.h"

#include "../../content/number-theory/ModularArithmetic.h"

int main() {
  const int mod = 17;
	rep(a,0,mod) rep(b,1,mod) {
		mint<int, 17> ma(a);
		mint<int, 17> mb(b);
		mint<int, 17> mc = ma / mb;
		assert((mc * mb).v == a);
	}
	mint<int, 17> a = 2;
	ll cur = 1;
	rep(i, 0, 17) {
		assert((a.pow(i)).v == cur);
		cur = (cur * 2) % mod;
		// cout << i << ": " << (a ^ i).x << endl;
	}
	cout<<"Tests passed!"<<endl;
}
