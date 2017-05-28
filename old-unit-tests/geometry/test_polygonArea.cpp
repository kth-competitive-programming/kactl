#include "../UnitTest.h"
#include "../../content/geometry/polygonArea.h"
#include <fstream>
#include <sstream>

class test_polygonArea :
	public UnitTest
{
public:
	test_polygonArea() : UnitTest("test_polygonArea") { }

	virtual ~test_polygonArea() { }

	virtual void run(int subcase) {
		typedef Point<double> P;
		vector<P> p;
		p.push_back(P(0,-2));
		p.push_back(P(1,-1));
		p.push_back(P(1,0));
		p.push_back(P(5,-1));
		check(polygonArea2<double>(p.begin(),p.end()),-8.0);

		const int N = 6;
		P poly[N] = {P(1,2),P(1,4),P(-1,4),P(2,5),P(2,3),P(3,2)};
		double A[N+1] = {0,0,0,4,-4,-6,-8};
		for (int i = 3; i <= N; ++i)
			check(polygonArea2<double>(poly,poly+i),A[i]);
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_polygonArea);
