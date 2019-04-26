#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/data-structures/FenwickTree2d.h"

int main() {
	rep(it,0,1000000) {
		FT2 ft(12);
		vector<tuple<int, int, int>> upd;
		int c = rand() % 20;
		rep(i,0,c) {
			upd.emplace_back(rand() % 12, rand() % 12, rand() % 10 - 5);
		}

		vector<vi> grid(12, vi(12)), sumto(13, vi(13));
		trav(pa, upd)
			ft.fakeUpdate(get<0>(pa), get<1>(pa));
		ft.init();
		trav(pa, upd) {
			grid[get<0>(pa)][get<1>(pa)] += get<2>(pa);
			ft.update(get<0>(pa), get<1>(pa), get<2>(pa));
		}

		rep(i,0,13) {
			rep(j,0,13) {
				ll v = ft.query(i, j);
				if (i == 0 || j == 0) assert(v == 0);
				else {
					sumto[i][j] = grid[i-1][j-1] + sumto[i-1][j] + sumto[i][j-1] - sumto[i-1][j-1];
					assert(v == sumto[i][j]);
				}
			}
		}
	}
}
