#include "../UnitTest.h"
#include "../../content/geometry/sphericalDistance.h"
#include <fstream>
#include <sstream>

class test_sphericalDistance :
	public UnitTest
{
public:
	test_sphericalDistance() : UnitTest("test_sphericalDistance") { }

	virtual ~test_sphericalDistance() { }

	virtual void run(int subcase) {
		check(sphericalDistance(0,0,0,0,5),0.0,"0");
		check(sphericalDistance(1,2,3,4,0),0.0,"0");
		check(sphericalDistance(0,0,1,0,10),0.0,"0");
		//check(sphericalDistance(2,M_PI,1,M_PI,10),0.0,"0");
		check(sphericalDistance(M_PI/2,M_PI/2,0,M_PI/2,10),5*M_PI,"0");
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_sphericalDistance);
