#include "../utilities/template.h"

#include "../../content/geometry/Point.h"

template<>
struct Point<double> {
	typedef Point P;
	typedef double T;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	Point(const Point<ll>& other) : x((double)other.x), y((double)other.y) {}
	P& operator=(const Point<ll>& other) { x = (double)other.x; y = (double)other.y; return *this; }
	bool operator==(const Point<ll>& other) const { return *this == P(other); }
	bool operator<(P p) const { return x<p.x||(x==p.x && y<p.y);}
	bool operator==(P p) const { return x==p.x && y==p.y; }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/LineHullIntersection.h"

int segmentIntersection(const P& s1, const P& e1,
		const P& s2, const P& e2, Point<double>& r1, Point<double>& r2) {
	if (e1==s1) {
		if (e2==s2) {
			if (e1==e2) { r1 = e1; return 1; } //all equal
			else return 0; //different point segments
		} else return segmentIntersection(s2,e2,s1,e1,r1,r2);//swap
	}
	//segment directions and separation
	P v1 = e1-s1, v2 = e2-s2, d = s2-s1;
	auto a = v1.cross(v2), a1 = v1.cross(d), a2 = v2.cross(d);
	if (a == 0) { //if parallel
		auto b1=s1.dot(v1), c1=e1.dot(v1),
		     b2=s2.dot(v1), c2=e2.dot(v1);
		if (a1 || a2 || max(b1,min(b2,c2))>min(c1,max(b2,c2)))
			return 0;
		r1 = min(b2,c2)<b1 ? s1 : (b2<c2 ? s2 : e2);
		r2 = max(b2,c2)>c1 ? e1 : (b2>c2 ? s2 : e2);
		return 2-(r1==r2);
	}
	if (a < 0) { a = -a; a1 = -a1; a2 = -a2; }
	if (0<a1 || a<-a1 || 0<a2 || a<-a2)
		return 0;
	typedef Point<double> PD;
	r1 = PD(s1) - PD(v1*a2)/(double)a;
	return 1;
}

int main() {
	srand(2);
	rep(it,0,1000000) {
		// cout<<endl;
		// cout<<"it: "<<it<<endl;
		int N = rand() % 15;
		vector<P> ps2;
		rep(i,0,N) ps2.emplace_back(rand() % 20 - 10, rand() % 20 - 10);
		vector<P> ps = convexHull(ps2);
		if (ps.empty()) continue;
		P p{rand() % 20 - 10, rand() % 20 - 10};
		P q{rand() % 20 - 10, rand() % 20 - 10};

		N = sz(ps);

		P delta = q - p, farp = p - delta * 50, farq = p + delta * 50;

		auto res = lineHull(p, q, ps);
		pii r = {res[0], res[1]};

		if (p == q) continue;

		auto fail = [&](int line) {
			cerr << sz(ps) << endl;
			for(auto &p: ps) cout << p<<' ';
			cout<<endl;
			cout << "line: "<<p<<' '<<q<<endl;
			cout << "-> " << r.first << ' ' << r.second << endl;
			cout << "@line " << line << endl;
			abort();
		};
#define FAIL() fail(__LINE__)

		int any = 0, gen = 0, corner = -1, waspar = 0;
		vector<pair<Point<double>, int>> hits;
		rep(iter,0,2) rep(i,0,N) {
			Point<double> r1, r2;
			int j = (i+1) % N;
			int qu = segmentIntersection(farp, farq, ps[i], ps[j], r1, r2);
			if (qu && (q - p).cross(ps[j] - ps[i]) == 0) { // parallel
				if (N != 2) {
					if (!(r.first == i || r.second == i)) FAIL();
				}
				// cerr << i << ' ' << j << ' ' << r.first << ' ' << r.second << endl;
				// assert(r.first == i && r.second == j);
				any = 1;
				if (iter == 0) gen = 10;
				waspar = 1;
			}
			else if (qu) {
				assert(qu != 2);
				if (r1 == ps[i]) {
					int k = (i-1+N) % N;
					if (!(r.first == i || r.second == i || r.first == k || r.second == k)) FAIL();
					if (iter == 1 && !waspar && !(r.first == i || r.second == i)) FAIL();
					if (iter == 0) corner = i;
					if (iter == 0) gen++;
					if (iter == 0) hits.emplace_back(r1, i);
				}
				else if (r1 == ps[j]) {
					if (!(r.first == i || r.second == i || r.first == j || r.second == j)) FAIL();
					if (iter == 1 && !waspar && !(r.first == j || r.second == j)) FAIL();
					if (iter == 0) corner = j;
					if (iter == 0) gen++;
				}
				else {
					if (!(r.first == i || r.second == i)) FAIL();
					if (iter == 0) gen = 10;
					if (iter == 0) hits.emplace_back(r1, i);
				}
				any = 1;
			}
		}

		if (!any) {
			assert(r.first == -1 && r.second == -1);
			continue;
		}
		if (!waspar) {
			if (r.first == r.second) FAIL();
		}
		if (gen == 2) {
			assert(r.first == corner);
			if (r.second != -1) FAIL();
		}
		if (N > 2 && (sz(hits) == 1) != (r.second == -1 || r.first == r.second)) {
			cout<<"res: "<<r.first<<' '<<r.second<<endl;
			FAIL();
		}
		assert(sz(hits) <= 2);
		if (r.first != r.second && sz(hits) == 2) {
			assert(r.second != -1);
			assert(hits[0].second != hits[1].second);
			assert(hits[0].second == r.first || hits[0].second == r.second);
			assert(hits[1].second == r.first || hits[1].second == r.second);
			double dist0 = (hits[0].first - Point<double>(p)).dot(delta);
			double dist1 = (hits[1].first - Point<double>(p)).dot(delta);
			if (hits[0].second == r.first) {
				if (!(dist0 <= dist1)) FAIL();
			}
			else {
				if (!(dist0 >= dist1)) FAIL();
			}
		}

		res = lineHull(q, p, ps);
		pii R = {res[0], res[1]};
		if (r.second == -1) {
			assert(R == r);
		}
		else if (N == 2 && r.first == r.second) {
			assert(R.first == R.second);
		}
		else {
			assert(R.first == r.second);
			assert(R.second == r.first);
		}
	}
	cout<<"Tests passed!"<<endl;
}
