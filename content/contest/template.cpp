#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(long long i = (a); i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define UNIQUE(x) (x).erase(unique(all(x)), (x).end())
using ll = long long;
using pii = pair<int, int>;
template <typename T> 
using vc = vector<T>;
using vi = vc<int>;
using vll = vc<ll>;

template <typename T1, typename T2>
inline bool chmin(T1 &a, T2 b) {
	if(a > b) { a = b; return true; }
	return false;
}

template <typename T1, typename T2>
inline bool chmax(T1 &a, T2 b) {
	if(a < b) { a = b; return true; }
	return false;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
}
