#include "../UnitTest.h"
#include "../../content/geometry/convexHull.h"
#include <fstream>
#include <sstream>
typedef Point<double> P;

template<class T>
ostream & operator<<(ostream & os, const vector<T> p) {
	os << "[ ";
	for(auto &it:p) os << it << " ";
	os << "]";
	return os;
}

class test_convexHull : public UnitTest {
public:
	ifstream in;
	int cases;
	test_convexHull() : UnitTest("test_convexHull") {
		ifstream file("convexHull.data");
		int N = 0, n;
		while (file >> n) {
			double d;
			rep(i,0,n) file >> d >> d;
			++N;
		}
		cases = N/2;
		file.close();

		in.open("convexHull.data");
	}

	virtual ~test_convexHull() {
		in.close();
	}

	vector<P> readPolygon() {
		int n;
		in >> n;
		vector<P> p(n);
		rep(i,0,n) in >> p[i];
		return p;
	}


	virtual void run(int subcase) {
		vector<P> p = readPolygon(), wanted = readPolygon();
		vector<P> res(p.begin(),convexHull(p.begin(),p.end()));

		sort(res.begin(),res.end());
		sort(wanted.begin(),wanted.end());
		stringstream ss;
		ss << p << endl << " -> " << res << endl << "!=" << wanted << endl;
		string s = ss.str();
		check(res.size(),wanted.size(),s);
		rep(i,0,res.size())
			if (!(res[i] == wanted[i]))
				fail(s);
	}

	void test(int subcase) {
	    run(subcase);
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
		return cases;
	}
};

KACTL_AUTOREGISTER_TEST(test_convexHull);
