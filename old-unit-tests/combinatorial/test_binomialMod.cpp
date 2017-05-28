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
			cases.push_back(pii(3127, 652));
			mod.push_back(10007);
			cases.push_back(pii(392, 86));
			mod.push_back(10007);
		}

		virtual ~test_binomialMod() {
		}

		virtual void run(int i) {
			int res = chooseModP((ll)cases[i].first, (ll)cases[i].second, mod[i]);
			if (i == 0) check(res, 1, "0");
			if (i == 1) check(res, 2, "1");
			if (i == 2) check(res, 12, "2");
			if (i == 3) check(res, 532, "3");
			if (i == 4) check(res, 4848, "4");
		}

		virtual int getCount() const {
			return cases.size();
		}
};

KACTL_AUTOREGISTER_TEST(test_binomialMod);
