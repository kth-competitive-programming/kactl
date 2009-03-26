#include "../UnitTest.h"
#include "../../geometry/Point.h"
#include "../../geometry/lineDist.h"
#include <fstream>
#include <sstream>

class test_lineDistDouble :
	public UnitTest
{
public:
	ifstream in,out;
	int cases;
	test_lineDistDouble() : UnitTest("test_lineDistDouble") {
		ifstream file("lineDistDouble.in");
		int n = 0; double d;
		while (file >> d) ++n;
		file.close();
		cases = n/6;

		in.open("lineDistDouble.in");
		out.open("lineDistDouble.out");
	}

	virtual ~test_lineDistDouble()
	{
	}



	template <class T>
	void test(T p1, T p2, T p3, double a) {
		stringstream ss;
		ss << p1 << " " << p2 << " " << p3;
		check(lineDist(p1,p2,p3), a, ss.str());
	}

	virtual void run(int subcase)
	{
		Point<double> p1,p2,p3;
		in >> p1 >> p2 >> p3;
		double a;
		out >> a;
		test(p1,p2,p3,a);
		test(p2,p1,p3,-a);
		test(p1*2,p2*2,p3*2,a*2);
		test(p2*2,p1*2,p3*2,-a*2);
		test(p1*9,p2*9,p3*9,a*9);
		test(p1*16,p2*16,p3*16,a*16);
		test(p2.perp(),p1.perp(),p3.perp(),-a);
		test(p2-p2,p1-p2,p3-p2,-a);
		test(p1+p3,p2+p3,p3+p3,a);
		test(p2.perp()*-1,p1.perp()*-1,p3.perp()*-1,-a);
	}

	virtual int getCount() const
	{
		return cases;
	}
};

KACTL_AUTOREGISTER_TEST(test_lineDistDouble);
