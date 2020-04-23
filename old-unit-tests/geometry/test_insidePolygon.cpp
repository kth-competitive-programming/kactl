#include "../UnitTest.h"
#include "../../content/geometry/insidePolygon.h"
#include <fstream>
#include <sstream>

const int tweaks = 5;

class test_insidePolygon :
	public UnitTest
{
public:
	vector<vector<Point<int> > > polys;
	vector<string> strings;
	vector<Point<int> > points;
	vector<int> answers;

	test_insidePolygon() : UnitTest("test_insidePolygon") {
		ifstream in("insidePolygon.in");
		int n;
		while (in >> n) {
			vector<Point<int> > poly(n);
			stringstream ss;
			rep(i,0,n) {
				in >> poly[i];
				ss << poly[i] << " ";
			}
			int q;
			in >> q;
			Point<int> p;
			rep(i,0,q) {
				in >> p;
				polys.push_back(poly);
				strings.push_back(ss.str());
				points.push_back(p);
			}
		}
		in.close();

		ifstream out("insidePolygon.out");
		answers.resize(points.size());
		rep(i,0,answers.size()) {
			out >> answers[i];
		}
	}

	virtual ~test_insidePolygon()
	{
	}

	virtual void run(int c)
	{
		if (c < points.size()) {
			bool a = insidePolygon(polys[c].begin(),
					polys[c].end(),points[c],false);
			stringstream ss;
			ss << strings[c] << " : " << points[c];
			check(a, (bool)answers[c], ss.str());
		} else {
			vector<Point<double> > poly(2+rand()%20);
			for(auto &i:poly) i = Point<double>(rand()%100000,rand()%100000);
			Point<double> p(rand()%100000,rand()%100000);
			bool a = insidePolygon(poly.begin(),poly.end(),p,true);
			for (int i = 0; i < 10; ++i) {
				double alpha = rand()%1000/1000.0;
				Point<double> D(rand()%1000,rand()%1000);
				for(auto &i:poly) i = i.rotate(alpha)+D;
				p = p.rotate(alpha)+D;
				check(insidePolygon(poly.begin(),poly.end(),p,true),a);
			}
		}
	}

	virtual int getCount() const
	{
		return points.size() + 20;
	}
};

KACTL_AUTOREGISTER_TEST(test_insidePolygon);
