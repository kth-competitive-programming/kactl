#include "../UnitTest.h"
#include "../../content/geometry/segmentIntersection.h"
#include <fstream>
#include <sstream>

class test_segmentIntersectionDouble :
	public UnitTest
{
public:
	ifstream in,out;
	int cases;
	test_segmentIntersectionDouble() : UnitTest("test_segmentIntersectionDouble") {
		ifstream file("segmentIntersectionDouble.in");
		int n = 0; double d;
		while (file >> d) ++n;
		file.close();
		cases = n/8;

		in.open("segmentIntersectionDouble.in");
		out.open("segmentIntersectionDouble.out");
	}

	virtual ~test_segmentIntersectionDouble() { }

	template <class T>
	void oldTest(T s1, T e1, T s2, T e2, vector<T> res) {
		stringstream ss;
		ss << s1 << " " << e1 << " " << s2 << " " << e2;
		vector<T> v(2);
		v.resize(segmentIntersection(s1,e1,s2,e2,v[0],v[1]));
		if (v != res)
			fail(ss.str());
		//check(v,res,ss.str());
	}
	template <class T>
	void test(T s1, T e1, T s2, T e2, int n, T r1, T r2) {
		stringstream ss;
		ss << s1 << " " << e1 << " " << s2 << " " << e2;
		T res1, res2;
		check(segmentIntersection(s1,e1,s2,e2,res1,res2),n,ss.str());
		if (n == 1) {
			ss << " " << n << " " << r1;
			check(r1,res1,ss.str());
		} else if (n == 2) {
			if ((!(r1==res1) || !(r2==res2)) && (!(r2==res1) || !(r1==res2)))
				fail(ss.str());
		}
	}

	template <class T>
	void test1(T s1, T e1, T s2, T e2, int n, T r1, T r2) {
		T p1(3,9), p2(-12409, 1421);
		test2(s1,e1,s2,e2,n,r1,r2);
		test2(s1+p1,e1+p1,s2+p1,e2+p1,n,r1+p1,r2+p1);
		test2(s1+p2,e1+p2,s2+p2,e2+p2,n,r1+p2,r2+p2);
	}
	template <class T>
	void test2(T s1, T e1, T s2, T e2, int n, T r1, T r2) {
		int p1 = 4, p2 = -3;
		test3(s1,e1,s2,e2,n,r1,r2);
		test3(s1*p1,e1*p1,s2*p1,e2*p1,n,r1*p1,r2*p1);
		test3(s1*p2,e1*p2,s2*p2,e2*p2,n,r1*p2,r2*p2);
	}
	template <class T>
	void test3(T s1, T e1, T s2, T e2, int n, T r1, T r2) {
		T s1p = s1.perp(),e1p = e1.perp(),s2p=s2.perp(),e2p=e2.perp(),
				r1p=r1.perp(),r2p=r2.perp();
		test4(s1,e1,s2,e2,n,r1,r2);
		test4(s1p,e1p,s2p,e2p,n,r1p,r2p);
		test4(s1+s1p,e1+e1p,s2+s2p,e2+e2p,n,r1+r1p,r2+r2p);
		test4(s1-s1p,e1-e1p,s2-s2p,e2-e2p,n,r1-r1p,r2-r2p);
		test4(s1*3-s1p,e1*3-e1p,s2*3-s2p,e2*3-e2p,n,r1*3-r1p,r2*3-r2p);
	}
	template <class T>
	void test4(T s1, T e1, T s2, T e2, int n, T r1, T r2) {
		test5(s1,e1,s2,e2,n,r1,r2);
		test5(s2,e2,s1,e1,n,r1,r2);
	}
	template <class T>
	void test5(T s1, T e1, T s2, T e2, int n, T r1, T r2) {
		test6(s1,e1,s2,e2,n,r1,r2);
		test6(e1,s1,s2,e2,n,r1,r2);
	}
	template <class T>
	void test6(T s1, T e1, T s2, T e2, int n, T r1, T r2) {
		test(s1,e1,s2,e2,n,r1,r2);
		test(s1,e1,e2,s2,n,r1,r2);
	}

	virtual void run(int subcase)
	{
		Point<double> p1,p2,p3,p4;
		in >> p1 >> p2 >> p3 >> p4;
		int n;
		out >> n;
		vector<Point<double> > v(2);
		rep(i,0,n) out >> v[i];

		test1(p1,p2,p3,p4,n,v[0],v[1]);
	}

	virtual int getCount() const
	{
		return cases;
	}
};

KACTL_AUTOREGISTER_TEST(test_segmentIntersectionDouble);
