/**
 * Author: hhhhaura
 * Date: 2022-8-18
 * Source: USACO guide
 * Description: Can deal with non-simple graphs. save normal edge
 * Time: Construction takes O(N).
 * status: untested
 */
struct BlockCutTree {
	int n, timestamp, id, ii;
	vector<int> L, D, pre;
	vector<vector<int>> mp, bcc;
	void init_(int _n) {
		n = _n, timestamp = 0;
		ii = 0, id = 0;
		L.assign(n + 1, 0);
		D.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
		bcc.assign(2 * n + 1, vector<int>());
	}
	void dfs(int x, int par) {
		D[x] = L[x] = ++timestamp;
		pre[ii++] = x;
		for(auto to : mp[x]) if(to != par) {
			if(D[to]) L[x] = min(L[x], D[to]);
			else {
				dfs(to, x);
				L[x] = min(L[x], L[to]);
				if(L[to] >= D[x]) {
					int cur = n + (++id);
					bcc[x].push_back(cur);
					while(pre[ii] != to) {
						ii --, bcc[cur].push_back(pre[ii]);
					}
				}
			}
		}
		
	}
};
