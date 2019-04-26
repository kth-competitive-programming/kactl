#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/data-structures/FenwickTree.h"

int main() {
	rep(it,0,100000) {
		int N = rand() % 10;
		FT fw(N);
		vi t(N);
		rep(i,0,N) {
			int v = rand() % 3;
			fw.update(i, v);
			t[i] += v;
		}
		int q = rand() % 20;
		int ind = fw.lower_bound(q);
		int res = -1, sum = 0;
		rep(i,0,N+1) {
			if (sum < q) res = i;
			if (i != N) sum += t[i];
		}
		assert(res == ind);
	}
}
