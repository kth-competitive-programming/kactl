#include "../UnitTest.h"
#include "../../content/various/intervalUnion.h"
#include <fstream>
#include <sstream>

typedef vector<pii> vpii;

class test_intervalUnion :
	public UnitTest
{
public:
	test_intervalUnion() : UnitTest("test_intervalUnion") { }

	virtual ~test_intervalUnion() { }

	void test(vpii s, vpii r) {
		vpii res = intervalUnion<int>(s.begin(),s.end());
		stringstream ss;
		trav(i,s) ss << "(" << i.first << "," << i.second << ")";
		ss << endl <<  " -> ";
		trav(i,res) ss << "(" << i.first << "," << i.second << ")";
		ss << endl << " != ";
		trav(i,r) ss << "(" << i.first << "," << i.second << ")";
		if (res != r)
			fail(ss.str());
	}

	virtual void run(int subcase) {
		if (subcase == 0) {
			vpii v;
			v.push_back(pii(1,3));
			v.push_back(pii(2,4));
			vpii r;
			r.push_back(pii(1,4));
			test(v,r);
		} else if (subcase == 1) {
			vpii v;
			v.push_back(pii(4,10));
			v.push_back(pii(1,3));
			v.push_back(pii(11,12));
			v.push_back(pii(2,4));
			vpii r;
			r.push_back(pii(1,10));
			r.push_back(pii(11,12));
			test(v,r);
		}
	}

	virtual int getCount() const {
		return 2;
	}
};

KACTL_AUTOREGISTER_TEST(test_intervalUnion);
