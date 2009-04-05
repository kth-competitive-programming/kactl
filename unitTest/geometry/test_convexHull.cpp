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
		P p1[3] = {P(1,1),P(3,2),P(1,5)};
		check(convexHull(p1,p1+3),p1+3);

		P p2[] = {P(0,0),P(1,0),P(2,0),P(2,1),P(2,2),P(1,2),P(0,2),P(0,1)};
		int n = convexHull(p2,p2+8)-p2;
		cout << endl << n << " ";
		rep(i,0,n) cout << p2[i] << " ";
		cout << endl;

		P p3[] = {P(0,0),P(1,0),P(2,0),P(2,1),P(2,2),P(1,2),P(0,2),P(1,1)};
		n = convexHull(p3,p3+8)-p3;
		cout << endl << n << " ";
		rep(i,0,n) cout << p2[i] << " ";
		cout << endl;
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_convexHull);
