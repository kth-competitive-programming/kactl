#include "../UnitTest.h"
#include "../../content/geometry/sideOf.h"
#include <fstream>
#include <sstream>

class test_sideOf :
	public UnitTest
{
public:
	test_sideOf() : UnitTest("test_sideOf") { }

	virtual ~test_sideOf() { }

	virtual void run(int subcase) {
		typedef Point<double> P;
		check(sideOf(P(0,0),P(1,0),P(1,1)),1);
		check(sideOf(P(0,0),P(1,0),P(1,0)),0);
		check(sideOf(P(0,0),P(1,0),P(1,-1)),-1);
		check(sideOf(P(1,0),P(0,0),P(1,1)),-1);
		check(sideOf(P(1,0),P(0,0),P(1,0)),0);
		check(sideOf(P(1,0),P(0,0),P(1,-1)),1);
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_sideOf);
