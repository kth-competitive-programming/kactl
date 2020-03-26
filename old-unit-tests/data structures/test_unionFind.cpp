#include "../UnitTest.h"
#include "../../content/data-structures/union_find.h"
#include <fstream>
#include <sstream>

typedef vector<pii> vpii;

class test_union_find :
	public UnitTest
{
public:
	test_union_find() : UnitTest("test_union_find") { }

	virtual ~test_union_find() { }

	virtual void run(int subcase) {
		if (subcase == 0) {
			union_find u(5);
			u.join(0, 1);
			if (u.sameSet(0, 2))
				fail("0 and 2 should not be in the same set");
			u.join(0, 2);
			if (u.size(2) != 3)
				fail("The size of the set where 2 is should be 3");
			if (!u.sameSet(0, 2))
				fail("0 and 2 should be in the same set");
			if (u.sameSet(3, 2))
				fail("3 and 2 should not be in the same set");
			if (u.size(3) != 1)
				fail("The size of the set where 3 is should be 1");
			u.join(3, 4);
			if (!u.sameSet(3, 4))
				fail("3 and 4 should be in the same set");
			if (u.sameSet(4, 2))
				fail("4 and 2 should not be in the same set");
			if (u.size(3) != 2)
				fail("The size of the set where 3 is should be 2");

		}
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_union_find);
