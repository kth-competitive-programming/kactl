#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(it, v) for(auto& it : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/number-theory/ModularArithmetic.h"

int main() {
	rep(a,0,mod) rep(b,1,mod) {
		Mod ma(a);
		Mod mb(b);
		Mod mc = ma / mb;
		assert((mc * mb).x == a);
	}
	Mod a = 2;
	rep(i,0,17) {
		cout << i << ": " << (a ^ i).x << endl;
	}
}
