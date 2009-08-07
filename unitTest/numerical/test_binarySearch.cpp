#include "../UnitTest.h"
#include "../../content/numerical/binarySearch.h"
#include <fstream>
#include <sstream>

double func1(double x) {
	return (x*x+1)*(x-3);
}

class test_binarySearch :
	public UnitTest
{
public:
	test_binarySearch() : UnitTest("test_binarySearch") { }

	virtual ~test_binarySearch() { }

	virtual void run(int subcase) {
		double e = 1e-6;
		if (subcase == 0) {
			double res = bs(-100,100,func1,e);
			if (abs(res-3) > e)
				fail("");
		} else if (subcase == 1) {
			double res = bs(2,100,func1,e);
			if (abs(res-3) > e)
				fail("");
		} else if (subcase == 2) {
			double res = bs(-10000,3,func1,e);
			if (abs(res-3) > e)
				fail("");
		} else if (subcase == 3) {
			double res = bs(4,9,sin,e)/2;
			if (abs(res-M_PI) > e)
				fail("");
		}
	}

	virtual int getCount() const {
		return 4;
	}
};

KACTL_AUTOREGISTER_TEST(test_binarySearch);
