#include "../utilities/template.h"

#include "../../content/geometry/CircleIntersection.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	srand(2);
	rep(it,0,100000) {
		double rnd[6];
		rep(i,0,6)
			rnd[i] = rand() % 21 - 10;
		P a(rnd[0], rnd[1]);
		P b(rnd[2], rnd[3]);
		double ra = rand() % 10;
		double rb = rand() % 10;
		if (a == b) continue;
		pair<P, P> out;
		bool ret = circleInter(a, b, ra, rb, &out);
		if (ret) {
			assert(abs((out.first - a).dist() - ra) < 1e-9);
			assert(abs((out.second - a).dist() - ra) < 1e-9);
			assert(abs((out.first - b).dist() - rb) < 1e-9);
			assert(abs((out.second - b).dist() - rb) < 1e-9);
		}

		// Hill-climb the answer
		auto func = [&](P x) {
			double d1 = (x - a).dist() - ra;
			double d2 = (x - b).dist() - rb;
			return d1*d1 + d2*d2;
		};
		P start = (a + b) / 2 + (a - b).perp();
		pair<double, P> cur(func(start), start);
		for (double jmp = 100; jmp > 1e-20; jmp /= 2) {
			int iters = 0;
			for (int imp = 1; imp--;) {
				if (++iters == 100) goto skip;
				rep(dx,-1,2) rep(dy,-1,2) {
					P p = cur.second;
					p.x += dx*jmp;
					p.y += dy*jmp;
					pair<double, P> np{func(p), p};
					if (np < cur) cur = np, imp = 1;
				}
			}
		}

		if (abs((cur.second - a).dist() - ra) < 1e-9 &&
		    abs((cur.second - b).dist() - rb) < 1e-9) {
			assert(ret);
			assert((out.first - cur.second).dist() < 1e-6 || (out.second - cur.second).dist() < 1e-6);
		} else {
			assert(!ret);
		}

		// cerr << '.';
		continue;
skip:;
		// Sometimes hill-climbing is slow, for some reason. :(
		// cerr << '#';
	}
	cout<<"Tests passed!"<<endl;
}
