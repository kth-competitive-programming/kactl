#include "../UnitTest.h"
#include "../../content/combinatorial/binomialModPrime.h"

class test_binomialMod :
	public UnitTest
{
	public:
		vector<pii> cases;
		vector<int> mod;

		test_binomialMod() : UnitTest("test_binomialMod") {
			cases.push_back(pii(4, 2));
			mod.push_back(5);
			cases.push_back(pii(14, 7));
			mod.push_back(7);
			cases.push_back(pii(12, 9));
			mod.push_back(13);
		}

		virtual ~test_binomialMod() {
		}

		virtual void run(int i) {
			int res = chooseModP((ll)cases[i].first, (ll)cases[i].second, mod[i]);
			if (i == 0) check(res, 1, "0");
			if (i == 1) check(res, 2, "1");
			if (i == 2) check(res, 12, "2");
		}

		virtual int getCount() const {
			return cases.size();
		}
};

KACTL_AUTOREGISTER_TEST(test_binomialMod);
