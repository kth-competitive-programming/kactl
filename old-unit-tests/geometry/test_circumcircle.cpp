#include "../UnitTest.h"
#include "../../content/geometry/circumcircle.h"
#include <fstream>
#include <sstream>

class test_circumcircle :
	public UnitTest
{
public:
	typedef Point<double> P;
	test_circumcircle() : UnitTest("test_circumcircle") { }

	virtual ~test_circumcircle() { }

	void test(P A, P B, P C, double r, P c) {
		stringstream ss;
		double rp = ccRadius(A,B,C);
		P cp = ccCenter(A,B,C);
		ss << A << B << C << " gives radius " << rp << " and center " << cp
				<< ". Expected radius " << r << " and center " << c;
		//cout << ss.str() << endl;
		if (abs(r-rp) > 1e-10 || (c-cp).dist() > 1e-10)
			fail(ss.str());
	}
	void test1(P A, P B, P C, double r, P c) {
		test(A,B,C,r,c);
		test(A,C,B,r,c);
		test(B,A,C,r,c);
		test(B,C,A,r,c);
		test(C,A,B,r,c);
		test(C,B,A,r,c);
	}

	virtual void run(int subcase) {
		test1(P(2,1),P(1,2),P(3,2), 1, P(2,2));
		test1(P(5,1),P(2,2),P(1,3), 5, P(5,6));
		test1(P(0,6),P(2,2),P(1,3), 5, P(5,6));
		test1(P(0,6),P(5,1),P(1,3), 5, P(5,6));
		test1(P(0,0),P(0,1),P(1,0), 1/sqrt(2), P(.5,.5));
		test1(P(0,0),P(0,1),P(0,2), 1/.0, P(.0/.0,.0/.0));
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_circumcircle);
