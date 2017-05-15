#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(x, v) for(auto& x : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/data structures/RMQ.h"

int main() {
	int N = 100;
	vi v(N);
	rep(i,0,N) v[i] = i;
	srand(2);
	random_shuffle(all(v));
	RMQ<int> rmq(v);
	rep(i,0,N) rep(j,i+1,N) {
		int m = rmq.query(i,j);
		int n = 1 << 29;
		rep(k,i,j) n = min(n, v[k]);
		assert(n == m);
	}
}
