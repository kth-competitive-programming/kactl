#include "../UnitTest.h"
#include "../../content/graph/dfs_matching.h"
#include <fstream>

class test_DFSMatching :
	public UnitTest
{
	public:
		ifstream in;
		ll cases;

		test_DFSMatching() : UnitTest("test_DFSMatching") {
			in.open("Matching.in");
			in >> cases;
		}

		virtual ~test_DFSMatching() {
			in.close();
		}

		virtual void run(ll subcase) {
			ll n, m, k;
			in >> n >> m >> k;
			vector<vector<ll> > g(n);
			for (ll i = 0; i < k; i++) {
				ll x, y; in >> x >> y;
				x--; y--;
				g[x].push_back(y);
			}
			ll res = dfs_matching(g, n, m);
			if (subcase == 0) check(res, 2, "DFS 0");
			if (subcase == 1) check(res, 43, "DFS 1");
			if (subcase == 2) check(res, 40, "DFS 2");
			if (subcase == 3) check(res, 40, "DFS 3");
			if (subcase == 4) check(res, 47, "DFS 4");
		}

		virtual ll getCount() const {
			return cases;
		}
};

KACTL_AUTOREGISTER_TEST(test_DFSMatching);
