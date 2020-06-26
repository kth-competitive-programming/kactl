#include "../utilities/template.h"
#include "../utilities/randGeo.h"

#include "../../content/geometry/lineDistance.h"
#include "../../content/geometry/CircleLine.h"

typedef Point<double> P;
int main() {
    {
        auto res = circleLine(P(0, 0), 1, P(-1, -1), P(1, 1));
        assert(res.size() == 2);
        assert((res[1]-P(sqrt(2)/2, sqrt(2)/2)).dist() < 1e-8);
    }
    {
        auto res = circleLine(P(0, 0), 1, P(-5,  1), P(5, 1));
        assert(res.size() == 1);
        assert((res[0]-P(0,1)).dist() < 1e-8);
    }
    {
        auto res = circleLine(P(4, 4), 1, P(0,  0), P(5, 0));
        assert(res.size() == 0);
    }
	rep(it,0,100000) {
		P a = randIntPt(5);
		P b = randIntPt(5);
		P c = randIntPt(5);
		if (a == b) {
			// Not a well defined line
			continue;
		}
		double r = sqrt(rand() % 49);
		vector<P> points = circleLine(c, r, a, b);

		// Soundness
		assert(sz(points) <= 2);
		for (P p : points) {
			// Point is on circle
			assert(abs((p - c).dist() - r) < 1e-6);
			// Point is on line
			assert(lineDist(a, b, p) < 1e-6);
		}

		// Best-effort completeness check:
		// in some easy cases we must have points in the intersection.
		if ((a - c).dist() < r - 1e-6 || (b - c).dist() < r - 1e-6 || ((a + b) / 2 - c).dist() < r - 1e-6) {
			assert(!points.empty());
		}
	}
    cout<<"Tests passed!"<<endl;
}
