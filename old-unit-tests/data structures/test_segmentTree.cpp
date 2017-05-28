#include "../UnitTest.h"
#include "../../content/data-structures/segmentTree.h"
#include <fstream>
#include <sstream>

typedef vector<pii> vpii;

class test_segmentTree :
	public UnitTest
{
public:
	test_segmentTree() : UnitTest("test_segmentTree") { }

	virtual ~test_segmentTree() { }

	virtual void run(int subcase) {
		if (subcase == 0) {
			int x[] = {0, 1, 2, 3, 4};
			Tree t(5);
			rep(i,0,5)
				t.update(i, x[i]);
			check(t.query(0, 2), 2, "0");
			check(t.query(2, 4), 4, "1");
			t.update(2, 6);
			check(t.query(2, 4), 6, "2");
			t.update(2, -2);
			t.update(4, -1);
			check(t.query(2, 4), 3, "3");
		}
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_segmentTree);
