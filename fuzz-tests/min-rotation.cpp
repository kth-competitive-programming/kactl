#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/strings/MinRotation.h"

int min_rotation2(string& v) {
	int n = sz(v);
	string w = v; w.insert(w.end(), all(v));
	int j = 0;
	rep(i,1,n) {
		if (vi(w.begin() + i, w.begin() + i + n) <
			vi(w.begin() + j, w.begin() + j + n)) j = i;
	}
	return j;
}

int main2() {
	rep(it,0,10000) {
		int n = rand() % 10;
		string v;
		rep(i,0,n) v += (char)(rand() % 3);
		int r = min_rotation(v);
		int r2 = min_rotation2(v);
		assert(r == r2);
		rotate(v.begin(), v.begin() + r, v.end());
		assert(min_rotation(v) == 0);
		assert(min_rotation2(v) == 0);
	}
	return 0;
}

int main() {
	string s;
	rep(i,0,10000000)
		s += (char)(rand()%400000 < 2);
	cout << min_rotation(s) << endl;
}
