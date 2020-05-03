#include "../utilities/template.h"

#include "../../content/geometry/DelaunayTriangulation.h"
#define ll double
#include "../../content/geometry/ConvexHull.h"
#undef ll
#include "../../content/geometry/PolygonArea.h"
#include "../../content/geometry/circumcircle.h"

typedef Point<double> P;
int main() {
	feenableexcept(29);
	rep(it,0,100000) {{
		vector<P> ps;
		int N = rand() % 20 + 1;
		rep(i,0,N) {
			ps.emplace_back(rand() % 100 - 50, rand() % 100 - 50);
		}

		auto coc = [&](int i, int j, int k, int l) {
			double a = (ps[i] - ps[j]).dist();
			double b = (ps[j] - ps[k]).dist();
			double c = (ps[k] - ps[l]).dist();
			double d = (ps[l] - ps[i]).dist();
			double e = (ps[i] - ps[k]).dist();
			double f = (ps[j] - ps[l]).dist();
			double q = a*c + b*d - e*f;
			return abs(q) < 1e-4;
		};

		rep(i,0,N) rep(j,0,i) rep(k,0,j) {
			if (ps[i].cross(ps[j], ps[k]) == 0) {  goto fail; }
		}
		rep(i,0,N) rep(j,0,i) rep(k,0,j) rep(l,0,k) {
			if (coc(i,j,k,l) || coc(i,j,l,k) || coc(i,l,j,k) || coc(i,l,k,j)) { goto fail; }
		}

		auto fail = [&]() {
			cout << "Points:" << endl;
			for(auto &p: ps) {
				cout << p.x << ' ' << p.y << endl;
			}

			cout << "Triangles:" << endl;
			delaunay(ps, [&](int i, int j, int k) {
				cout << i << ' ' << j << ' ' << k << endl;
			});

			abort();
		};

		double sumar = 0;
		vi used(N);
		delaunay(ps, [&](int i, int j, int k) {
			used[i] = used[j] = used[k] = 1;
			double ar = ps[i].cross(ps[j], ps[k]);
			if (ar < -1e-4) fail();
			sumar += ar;
			P c = ccCenter(ps[i], ps[j], ps[k]);
			double ra = ccRadius(ps[i], ps[j], ps[k]);
			rep(l,0,N) {
				if ((ps[l] - c).dist() < ra - 1e-5) fail();
			}
		});
		if (N >= 3) rep(i,0,N) if (!used[i]) fail();

		vector<P> hull = convexHull(ps);
		double ar2 = polygonArea2(hull);
		if (abs(sumar - ar2) > 1e-4) fail();

		continue; }
fail:;
	}
	cout<<"Tests passed!"<<endl;
}
