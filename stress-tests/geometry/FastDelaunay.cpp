#include "../utilities/template.h"

// #define TEST_PERF

#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/PolygonArea.h"

#define P P2
#include "../../content/geometry/circumcircle.h"
#undef P

P2 top(P x) { return P2((double)x.x, (double)x.y); }

struct Bumpalloc {
	char buf[450 << 20];
	size_t bufp;
	void* alloc(size_t s) {
		assert(s < bufp);
		return (void*)&buf[bufp -= s];
	}
	Bumpalloc() { reset(); }

	template<class T> T* operator=(T&& x) {
		T* r = (T*)alloc(sizeof(T));
		new(r) T(move(x));
		return r;
	}
	void reset() { bufp = sizeof buf; }
} bumpalloc;

// When not testing perf, we don't want to leak memory
#ifndef TEST_PERF
#define new bumpalloc =
#endif
#include "../../content/geometry/FastDelaunay.h"
#ifndef TEST_PERF
#undef new
#endif

template<class A, class F>
void dela(A& v, F f) {
	auto ret = triangulate(v);
	assert(sz(ret) % 3 == 0);
	map<P, int> lut;
	rep(i,0,sz(v)) lut[v[i]] = i;
	for (int a = 0; a < sz(ret); a += 3) {
		f(lut[ret[a]], lut[ret[a+1]], lut[ret[a+2]]);
	}
}

int main1() {
	srand(2);
	feenableexcept(29);
	rep(it,0,3000000) {{
		bumpalloc.reset();
		// if (it % 200 == 0) cerr << endl;
		vector<P> ps;
		int N = rand() % 20 + 1;
		int xrange = rand() % 50 + 1;
		int yrange = rand() % 50 + 1;
		rep(i,0,N) {
			ps.emplace_back(rand() % (2*xrange) - xrange, rand() % (2*yrange) - yrange);
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

		rep(i,0,N) rep(j,0,i) {
			// identical
			if (ps[i] == ps[j]) {  goto fail; }
		}
		if (false) rep(i,0,N) rep(j,0,i) rep(k,0,j) {
			// colinear
			if (ps[i].cross(ps[j], ps[k]) == 0) {  goto fail; }
		}
		if (false) rep(i,0,N) rep(j,0,i) rep(k,0,j) rep(l,0,k) {
			// concyclic
			if (coc(i,j,k,l) || coc(i,j,l,k) || coc(i,l,j,k) || coc(i,l,k,j)) {  goto fail; }
		}

		bool allColinear = true;
		if (N >= 3) {
			rep(i,2,N) if ((ps[i] - ps[0]).cross(ps[1] - ps[0])) allColinear = false;
		}

		auto fail = [&]() {
			cout << "Points:" << endl;
			for(auto &p: ps) {
				cout << p.x << ' ' << p.y << endl;
			}

			cout << "Triangles:" << endl;
			dela(ps, [&](int i, int j, int k) {
				cout << i << ' ' << j << ' ' << k << endl;
			});

			abort();
		};

		ll sumar = 0;
		vi used(N);
		bool any = false;
		dela(ps, [&](int i, int j, int k) {
			any = true;
			used[i] = used[j] = used[k] = 1;
			ll ar = ps[i].cross(ps[j], ps[k]);
			if (ar <= 0) fail();
			sumar += ar;
			P2 c = ccCenter(top(ps[i]), top(ps[j]), top(ps[k]));
			double ra = ccRadius(top(ps[i]), top(ps[j]), top(ps[k]));
			rep(l,0,N) {
				if ((top(ps[l]) - c).dist() < ra - 1e-5) fail();
			}
		});
		if (!allColinear) {
			rep(i,0,N) if (!used[i]) fail();
		} else {
			assert(!any);
		}

		vector<P> hull = convexHull(ps);
		ll ar2 = polygonArea2(hull);
		if (ar2 != sumar) fail();

		continue; }
fail:;
	}
	cout<<"Tests passed!"<<endl;
	// cerr << endl;
	return 0;
}

int main2() {
	vector<P> ps;
	int N = 100000;
	int xrange = 20000;
	int yrange = 20000;
	rep(i,0,N) {
		ps.emplace_back(rand() % (2*xrange) - xrange, rand() % (2*yrange) - yrange);
	}
	sort(all(ps));
	ps.erase(unique(all(ps)), ps.end());

	cout << sz(ps) << endl;
	triangulate(ps);
	return 0;
}

#ifdef TEST_PERF
int main() { return main2(); }
#else
int main() { return main1(); }
#endif
