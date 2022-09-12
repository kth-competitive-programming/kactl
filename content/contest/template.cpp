#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#ifdef NONTOI
#define debug(args...) LKJ("\033[1;32m[ " #args " ]\033[0m", args)
template<class I> void LKJ(I&&x){ cerr << x << '\n'; }
template<class I, class...T> void LKJ(I&&x, T&&...t){ cerr << x << ", ", LKJ(t...); }
template<class I> void print(I a, I b){ while(a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define print(...) 0
#endif

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
}
