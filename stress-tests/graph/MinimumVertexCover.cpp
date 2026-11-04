#include "../utilities/template.h"

#include "../../content/graph/MinimumVertexCover.h"
#include "../../content/graph/HopcroftKarp.h"

vi coverHK(vector<vi>& g, int n, int m) {
	vi match(m, -1);
	int res = hopcroftKarp(g, match);
	vector<bool> lfound(n, true), seen(m);
	for(auto &it: match) if (it != -1) lfound[it] = false;
	vi q, cover;
	rep(i,0,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for(auto &e: g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.push_back(match[e]);
		}
	}
	rep(i,0,n) if (!lfound[i]) cover.push_back(i);
	rep(i,0,m) if (seen[i]) cover.push_back(n+i);
	assert(sz(cover) == res);
	return cover;
}

int main() {
	const int MAXN = 20;
	mt19937 rng(17);
	rep(it,0,300'000) {
		int N = rand() % MAXN, M = rand() % MAXN;
		vector<vi> gr(N);
		int co = rand() % 128 < 10 ? 2 : 1;
		rep(_,0,co) {
			int prop = rand();
			if (max(N, M) >= 5 && rand() % 128 < 90) {
				prop /= max(N, M);
				prop *= 2;
			}
			rep(i,0,N) rep(j,0,M) if (rand() < prop) {
				gr[i].push_back(j);
			}
		}
		if (rand() % 128 < 20 && N && M) {
			int paths = rand() % min(N, M);
			vi left(N), right(M);
			rep(i,0,N) left[i] = i;
			rep(i,0,M) right[i] = i;
			rep(_,0,paths) {
				shuffle(all(left), rng);
				shuffle(all(right), rng);
				int len = rand() % min(N, M) + 1;
				if (rand() & 128) gr[left[0]].push_back(right[0]);
				rep(i,1,len-1) {
					gr[left[i]].push_back(right[i-1]);
					gr[left[i]].push_back(right[i]);
				}
				if (len > 1 && (rand() & 128)) gr[left.back()].push_back(right.back());
			}
		}
		rep(i,0,N) {
			// Duplicate edges are okay
			// sort(all(gr[i]));
			// gr[i].erase(unique(all(gr[i])), gr[i].end());
			shuffle(all(gr[i]), rng);
		}
		auto verify = [&](vi& cover) {
			vi left(N), right(M);
			for(auto &x: cover) {
				if (x < N) left[x] = 1;
				else right[x - N] = 1;
			}
			rep(i,0,N) if (!left[i]) for(auto &j:gr[i]) {
				assert(right[j]);
				/* if (!right[j]) {
					cout << N << ' ' << M << endl;
					rep(i,0,N) for(auto &j: gr[i]) cout << i << " - " << j << endl;
					cout << "yields " << sz(cover) << endl;
					for(auto &x: cover) cout << x << endl;
					abort();
				} */
			}
		};
		vi cover1 = cover(gr, N, M);
		vi cover2 = coverHK(gr, N, M);
		assert(sz(cover1) == sz(cover2));
		verify(cover1);
		verify(cover2);
		// cout << '.' << endl;
	}
	cout<<"Tests passed!"<<endl;
}
