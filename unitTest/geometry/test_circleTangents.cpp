#include "../UnitTest.h"
#include "../../content/geometry/circleTangents.h"
#include <fstream>
#include <sstream>

class test_circleTangents :
	public UnitTest
{
public:
	test_circleTangents() : UnitTest("test_circleTangents") { }

	virtual ~test_circleTangents() { }

	virtual void run(int subcase) {
		typedef Point<double> P;
		pair<P,P> p = circleTangents(P(100,1),P(0,0),1);
		cout << p.first << p.second << endl;
		p = circleTangents(P(104,106),P(100,100),1);
		cout << p.first << p.second << endl;
		p = circleTangents(P(104,106),P(100,100),2);
		cout << p.first << p.second << endl;
		p = circleTangents(P(100,100),P(104,106),1);
		cout << p.first << p.second << endl;
		p = circleTangents(P(0,0),P(1,0),2);
		cout << p.first << p.second << endl;
	}

	virtual int getCount() const {
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_circleTangents);
