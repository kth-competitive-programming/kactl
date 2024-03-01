#include "../UnitTest.h"
#include "../../content/graph/hopcroftKarp.h"
#include <fstream>

class test_HopcorftKarp :
	public UnitTest
{
	public:
		ifstream in;
		ll cases;

		test_HopcorftKarp() : UnitTest("test_HopcorftKarp") {
			in.open("Matching.in");
			in >> cases;
		}

		virtual ~test_HopcorftKarp() {
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
			vi b(m, -1);
			ll res = hopcroftKarp(g, b);
			if (subcase == 0) check(res, 2, "0");
			if (subcase == 1) check(res, 43, "1");
			if (subcase == 2) check(res, 40, "2");
			if (subcase == 3) check(res, 40, "3");
			if (subcase == 4) check(res, 47, "4");
		}

		virtual ll getCount() const {
			return cases;
		}
};

KACTL_AUTOREGISTER_TEST(test_HopcorftKarp);
