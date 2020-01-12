#include "../utilities/template.h"

#include "../../content/geometry/lineIntersection.h"
#include "../../content/geometry/lineDistance.h"

int main() {
	rep(t,0,1000000) {
		const int GRID=10;
		Point<double>
			a(rand()%GRID, rand()%GRID),
			b(rand()%GRID, rand()%GRID),
			c(rand()%GRID, rand()%GRID),
			d(rand()%GRID, rand()%GRID);
		auto pa = lineInter(a,b,c,d);
		if (pa.first == 1) {
			assert(lineDist(a, b, pa.second) < 1e-8);
			assert(lineDist(c, d, pa.second) < 1e-8);
		}
	}
	cout<<"Tests passed!"<<endl;
}
