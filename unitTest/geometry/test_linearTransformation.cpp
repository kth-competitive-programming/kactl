#include "../UnitTest.h"
#include "../../content/geometry/linearTransformation.h"
#include <fstream>
#include <sstream>

class test_linearTransformation :
	public UnitTest
{
public:
	test_linearTransformation() : UnitTest("test_linearTransformation") { }

	virtual ~test_linearTransformation() { }

	virtual void run(int subcase) {
		typedef Point<double> P;
		check(linearTransformation(P(0,0),P(1,0),P(1,1),P(1,2),P(2,1)),P(0,3));
		check(linearTransformation(P(1,1),P(5,4),P(2,-1),P(4,-3),P(8,0)),P(2,-5));
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_linearTransformation);
