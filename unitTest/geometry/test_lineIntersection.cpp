#include "../UnitTest.h"
#include "../../content/geometry/lineIntersection.h"
#include <fstream>
#include <sstream>

class test_lineIntersection :
	public UnitTest
{
public:
	test_lineIntersection() : UnitTest("test_lineIntersection") { }

	virtual ~test_lineIntersection() { }

	virtual void run(int subcase) {
		typedef Point<double> P;
		P r;
		check(lineIntersection(P(0,0),P(1,0),P(0,2),P(1,1),r),1);
		if (!(r==P(2,0)))
			fail("1");
		check(lineIntersection(P(0,0),P(1,0),P(6,-1),P(0,2),r),1);
		if (!(r==P(4,0)))
			fail("2");
		check(lineIntersection(P(1,2),P(3,4),P(-5,1),P(-3,2),r),1);
		if (!(r==P(5,6)))
			fail("3");
		check(lineIntersection(P(1,2),P(2,4),P(5,-1),P(1,-9),r),0);
		check(lineIntersection(P(1,2),P(2,4),P(9,18),P(7,14),r),-1);
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_lineIntersection);
