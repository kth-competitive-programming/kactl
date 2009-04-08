#include "../UnitTest.h"
#include "../../content/geometry/polygonCenter.h"
#include <fstream>
#include <sstream>

class test_polygonCenter :
	public UnitTest
{
public:
	test_polygonCenter() : UnitTest("test_polygonCenter") { }

	virtual ~test_polygonCenter() { }

	virtual void run(int subcase) {
		typedef Point<double> P;
		if (subcase == 0) {
			P p[] = {P(0,0),P(3,0),P(0,3)};
			check(polygonCenter(p,p+3),P(1,1));
		} else if (subcase == 1) {
			P p[] = {P(5,2),P(8,2),P(5,5)};
			check(polygonCenter(p,p+3),P(6,3));
		} else if (subcase == 2) {
			P p[] = {P(0,0),P(0,2),P(2,2),P(2,0)};
			check(polygonCenter(p,p+4),P(1,1));
		} else if (subcase == 3) {
			P p[] = {P(0,0),P(2,0),P(2,2),P(0,2)};
			check(polygonCenter(p,p+4),P(1,1));
		} else if (subcase == 4) {
			P p[] = {P(1,1),P(3,1),P(5,3),P(3,3)};
			check(polygonCenter(p,p+4),P(3,2));
		} else if (subcase == 5) {
			P p[] = {P(1,1),P(2,1),P(3,1),P(4,2),P(5,3),P(3,3)};
			check(polygonCenter(p,p+6),P(3,2));
		} else if (subcase == 6) {
			P p[] = {P(1,1),P(1,4),P(3,4),P(4,3),P(5,4),P(5,1)};
			rep(i,0,6) p[i]=p[i]*6*11;
			check(polygonCenter(p,p+6),P(192,158));
		} else if (subcase == 7) {
			P p[] = {P(0,0),P(3,3),P(0,3)};
			check(polygonCenter(p,p+3),P(1,2));
		} else if (subcase == 8) {
			P p[] = {P(3,0),P(3,3),P(0,3)};
			check(polygonCenter(p,p+3),P(2,2));
		}
	}

	virtual int getCount() const {
		return 9;
	}
};

KACTL_AUTOREGISTER_TEST(test_polygonCenter);
