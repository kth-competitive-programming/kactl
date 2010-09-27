#include "../UnitTest.h"
#include "../../content/data structures/union_find.h"
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
			if (u.same_set(0, 2))
				fail("0 and 2 should not be in the same set");
			u.join(0, 2);
			if (!u.same_set(0, 2))
				fail("0 and 2 should be in the same set");
			if (u.same_set(3, 2))
				fail("3 and 2 should not be in the same set");
			u.join(3, 4);
			if (!u.same_set(3, 4))
				fail("3 and 4 should be in the same set");
			if (u.same_set(4, 2))
				fail("4 and 2 should not be in the same set");
		}
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_union_find);
