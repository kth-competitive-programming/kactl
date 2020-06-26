#include "../utilities/template.h"

#include "../../content/geometry/PolygonArea.h"
#include "../../content/geometry/PolygonCenter.h"
#include "../../content/geometry/InsidePolygon.h"

int main() {
	srand(0);
	typedef Point<double> P;
	vector<P> ps = {P{0,0}, P{6,4}, P{0,9}};
	int count = 0;
	P su{0,0};
	rep(it,0,100000) {
		double x = rand() / (RAND_MAX + 1.0);
		double y = rand() / (RAND_MAX + 1.0);
		x *= 10;
		y *= 10;
		if (!inPolygon(ps, P{x,y}, true)) continue;
		count++;
		su = su + P{x,y};
	}
	su = su / count;
	double approxArea = (double)count / 100000 * 100;
	assert(abs(polygonArea2(ps)/2.0 - approxArea) < 1);
	auto p = polygonCenter(ps);
	assert(abs(p.x - su.x) < 1e-1 && abs(p.y - su.y) < 1e-1);
	cout<<"Tests passed!"<<endl;
}
