#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
using namespace std;

#define rep(i, a, b) for(int i = (a); i < (b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool solve(int tc) {
	int n = rand()%100+3;
	cout << n << endl;
	rep(i,0,n) cout << rand()%20000-10000 << " " << rand()%20000-10000 << endl;
	return true;
}

int main() {
	int n = 0;
	if(!n) cin >> n;
	for(int i = 0; i < n && solve(i); ++i);
	return 0;
}
