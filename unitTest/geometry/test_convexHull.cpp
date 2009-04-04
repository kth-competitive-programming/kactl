#include "../UnitTest.h"
#include "../../geometry/Point.h"
#include "../../geometry/convexHull.h"
#include <fstream>
#include <sstream>

class test_convexHull :
	public UnitTest
{
public:
	test_convexHull() : UnitTest("test_convexHull") { }

	virtual ~test_convexHull() { }

	virtual void run(int subcase) {
		typedef Point<double> P;
		P p[3] = {P(1,1),P(3,2),P(1,5)};
		convexHull(p,p+3);
		//check(convexHull(P(0,0),P(1,0),P(1,1)),1);
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_convexHull);
