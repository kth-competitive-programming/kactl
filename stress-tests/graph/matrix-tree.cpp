#include "../utilities/template.h"

ll det(vector<vector<ll>>& a) {
	int n = sz(a); ll ans = 1;
	rep(i,0,n) {
		rep(j,i+1,n) {
			while (a[j][i] != 0) { // gcd step
				ll t = a[i][i] / a[j][i];
				if (t) rep(k,i,n)
					a[i][k] = (a[i][k] - a[j][k] * t);
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		ans = ans * a[i][i];
		if (!ans) return 0;
	}
	return ans;
}

ll rec(vector<vi>& ed, int active, int finished) {
	int N = sz(ed);
	if (finished == (1 << N) - 1) return 1;
	int chosen = -1;
	rep(i,0,N) if (!(finished & (1 << i)) && (active & (1 << i))) {
		chosen = i;
		break;
	}
	if (chosen == -1) return 0; // missing nodes from tree
	int si = sz(ed[chosen]);
	ll res = 0;
	rep(bi,0,(1 << si)) {
		int edto = 0;
		rep(i,0,si) {
			if (bi & (1 << i)) {
				if (edto & (1 << ed[chosen][i])) goto fail;
				edto |= 1 << ed[chosen][i];
			}
		}
		if (active & edto) continue;
		res += rec(ed, active | edto, finished | (1 << chosen));
fail:;
	}
	return res;
}

ll countTrees(vector<vi>& ed, int root) {
	return rec(ed, 1 << root, 0);
}

int main() {
	rep(it,0,100) {
		int N = rand() % 7 + 1;
		int M = rand() % 10;
		int root = rand() % N;
		vector<vi> ed(N);
		vector<vector<ll>> mat(N, vector<ll>(N));
		rep(i,0,M) {
			int a = rand() % N;
			int b = rand() % N;
			ed[a].push_back(b);
			mat[b][b]++;
			mat[a][b]--;
		}
		ll numTrees = countTrees(ed, root);

		mat.erase(mat.begin() + root);
		rep(i,0,N-1) mat[i].erase(mat[i].begin() + root);

		ll numTrees2 = det(mat);
		assert(numTrees == numTrees2);
	}
	cout << "Tests passed!" << endl;
}
