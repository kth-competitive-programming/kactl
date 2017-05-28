#include "../UnitTest.h"
#include "../../content/combinatorial/multinomial.h"

class test_multinomial :
	public UnitTest
{
	public:
		vector<vector<int> > cases;

		test_multinomial() : UnitTest("test_multinomial") {
			vector<int> a(2, 2);
			cases.push_back(a);
			a.clear();
			a.push_back(3); a.push_back(4); a.push_back(5);
			cases.push_back(a);
		}

		virtual ~test_multinomial() {
		}

		virtual void run(int i) {
			int res = multinomial<int, vector<int> >(cases[i].size(), cases[i]);
			if (i == 0)
				check(res, 6, "0");
			if (i == 1)
				check(res, 27720, "0");
		}

		virtual int getCount() const {
			return cases.size();
		}
};

KACTL_AUTOREGISTER_TEST(test_multinomial);
