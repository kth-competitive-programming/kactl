#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/geometry/HalfPlane.h"
#include "../../content/geometry/PolygonArea.h"
typedef Point<double> P;

ostream &operator<<(ostream &os, P p) { return cout << "(" << p.x << "," << p.y << ")"; }

namespace MIT {
#define eps 1e-8
typedef Point<double> P;

template<class P>
pair<int, P> lineIntersection(P s1, P e1, P s2, P e2) {
	auto d = (e1-s1).cross(e2-s2);
	if (d == 0)  //if parallel
		return {-((e1-s1).cross(s2-s1)==0 || s2==e2), P(0,0)};
	else
		return {1, s2-(e2-s2)*(e1-s1).cross(s2-s1)/d};
}

struct Line {
	P P1, P2;
	// Right hand side of the ray P1 -> P2
	explicit Line(P a = P(), P b = P()) : P1(a), P2(b) {};
	P intpo(Line y) {
		auto res = lineIntersection(P1, P2, y.P1, y.P2);
		assert(res.first == 1);
		return res.second;
	}
	P dir() {
		return P2 - P1;
	}
	bool contains(P x) {
		return (P2 - P1).cross(x - P1) < eps;
	}
	bool out(P x) {
		return !contains(x);
	}
};

template<class T>
bool mycmp(Point<T> a, Point<T> b) {
	// return atan2(a.y, a.x) < atan2(b.y, b.x);
	if (a.x * b.x < 0)	return a.x < 0;
	if (abs(a.x) < eps) {
		if (abs(b.x) < eps) 	return a.y > 0 && b.y < 0;
		if (b.x < 0)	return a.y > 0;
		if (b.x > 0)	return true;
	}
	if (abs(b.x) < eps) {
		if (a.x < 0)	return b.y < 0;
		if (a.x > 0)	return false;
	}
	return a.cross(b) > 0;
}

bool cmp(Line a, Line b) {
	return mycmp(a.dir(), b.dir());
}

double Intersection_Area(vector <Line> b) {
	sort(b.begin(), b.end(), cmp);
	int n = b.size();
	int q = 1, h = 0, i;
	vector <Line> ca(b.size() + 10);
	for (i = 0; i < n; i++) {
		while (q < h && b[i].out(ca[h].intpo(ca[h - 1])))	h--;
		while (q < h && b[i].out(ca[q].intpo(ca[q + 1])))	q++;
		ca[++h] = b[i];
		if (q < h && abs(ca[h].dir().cross(ca[h - 1].dir())) < eps) {
			h--;
			if (b[i].out(ca[h].P1))	ca[h] = b[i];
		}
	}
	while (q < h - 1 && ca[q].out(ca[h].intpo(ca[h - 1])))	h--;
	while (q < h - 1 && ca[h].out(ca[q].intpo(ca[q + 1])))	q++;
	// Intersection is empty. This is sometimes different from the case when
	// the intersection area is 0.
	if (h - q <= 1)	return 0;
	ca[h + 1] = ca[q];
	vector <P> s;
	for (i = q; i <= h; i++)	s.push_back(ca[i].intpo(ca[i + 1]));
	s.push_back(s[0]);
	double ans = 0;
	for (i = 0; i < (int) s.size() - 1; i++)	ans += s[i].cross(s[i + 1]);
	return ans / 2;
}
}
vector<MIT::Line> convert(vector<Line> x) {
    vector<MIT::Line> res;
    for (auto i: x)
        res.push_back(MIT::Line(i[1], i[0]));
    return res;
}

const double INF = 1e9;
void addInf(vector<Line> &res) {
    vector<P> infPts({P(INF, INF), P(-INF, INF), P(-INF, -INF), P(INF, -INF)});
    for (int i=0; i<4; i++)
        res.push_back({infPts[i], infPts[(i+1)%4]});
}
void test1() {
    vector<Line> t({{P(0,0),P(5,0)}, {P(5,-2), P(5,2)}, {P(5,2),P(2,2)}, {P(0,3),P(0,-3)}});
    auto res = halfPlaneIntersection(t);
    cout<<MIT::Intersection_Area(convert(t))<<endl;
    assert(polygonArea2(res) == 20);
    addInf(t);
    res = halfPlaneIntersection(t);
    assert(polygonArea2(res) == 20);
}
void testInf() {
    vector<Line> t({{P(0,0), P(5,0)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(polygonArea2(res)/4e18);
    t = vector<Line>({{P(0,0), P(5,0)}, {P(0,0), P(0,5)}});
    addInf(t);
    res = halfPlaneIntersection(t);
    assert(polygonArea2(res)/2e18 == 1);
}
void testLine() {
    vector<Line> t({{P(0,0), P(5,0)}, {P(5,0), P(0,0)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(sz(res) >= 2);
    assert(polygonArea2(res) == 0);
}
void testPoint() {
    vector<Line> t({{P(0,0), P(5,0)}, {P(5,0), P(0,0)}, {P(0,0), P(0,5)}, {P(0,5), P(0,0)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(sz(res) >= 1);
    assert(polygonArea2(res) == 0);
}
void testEmpty() {
    vector<Line> t({{P(0,0), P(5,0)}, {P(5,0), P(0,0)}, {P(0,0), P(0,5)}, {P(0,5), P(0,0)},
                    {P(0,2), P(5,2)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(sz(res) == 0);
}

int main() {
    test1();
    testInf();
    testLine();
    testPoint();
    testEmpty();
}
