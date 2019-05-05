#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < int(b); ++i)
#define trav(a, v) for (auto &a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/geometry/HalfPlane.h"
#include "../../content/geometry/PolygonArea.h"
typedef Point<double> P;

ostream &operator<<(ostream &os, P p) { return cout << "(" << p.x << "," << p.y << ")"; }

namespace sjtu {
const double EPS = 1e-8;
inline int sign(double a) { return a < -EPS ? -1 : a > EPS; }
struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double d) const { return Point(x * d, y * d); }
    Point operator/(double d) const { return Point(x / d, y / d); }
    bool operator<(const Point &p) const {
        int c = sign(x - p.x);
        if (c)
            return c == -1;
        return sign(y - p.y) == -1;
    }
    double dot(const Point &p) const { return x * p.x + y * p.y; }
    double det(const Point &p) const { return x * p.y - y * p.x; }
    double alpha() const { return atan2(y, x); }
    double distTo(const Point &p) const {
        double dx = x - p.x, dy = y - p.y;
        return hypot(dx, dy);
    }
    double alphaTo(const Point &p) const {
        double dx = x - p.x, dy = y - p.y;
        return atan2(dy, dx);
    }
    // clockwise
    Point rotAlpha(const double &alpha, const Point &o = Point(0, 0)) const {
        double nx = cos(alpha) * (x - o.x) + sin(alpha) * (y - o.y);
        double ny = -sin(alpha) * (x - o.x) + cos(alpha) * (y - o.y);
        return Point(nx, ny) + o;
    }
    Point rot90() const { return Point(-y, x); }
    Point unit() { return *this / abs(); }
    void read() { scanf("%lf%lf", &x, &y); }
    double abs() { return hypot(x, y); }
    double abs2() { return x * x + y * y; }
    void write() { cout << "(" << x << "," << y << ")" << endl; }
};
#define cross(p1, p2, p3) ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y))
#define crossOp(p1, p2, p3) sign(cross(p1, p2, p3))

Point isSS(Point p1, Point p2, Point q1, Point q2) {
    double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}
struct Border {
    Point p1, p2;
    double alpha;
    void setAlpha() { alpha = atan2(p2.y - p1.y, p2.x - p1.x); }
    void read() {
        p1.read();
        p2.read();
        setAlpha();
    }
};

int n;
const int MAX_N_BORDER = 20000 + 10;
Border border[MAX_N_BORDER];

bool operator<(const Border &a, const Border &b) {
    int c = sign(a.alpha - b.alpha);
    if (c != 0)
        return c == 1;
    return crossOp(b.p1, b.p2, a.p1) >= 0;
}

bool operator==(const Border &a, const Border &b) { return sign(a.alpha - b.alpha) == 0; }

void add(double x, double y, double nx, double ny) {
    border[n].p1 = Point(x, y);
    border[n].p2 = Point(nx, ny);
    border[n].setAlpha();
    n++;
}

Point isBorder(const Border &a, const Border &b) { return isSS(a.p1, a.p2, b.p1, b.p2); }

Border que[MAX_N_BORDER];
int qh, qt;

bool check(const Border &a, const Border &b, const Border &me) {
    Point is = isBorder(a, b);
    return crossOp(me.p1, me.p2, is) > 0;
}

void convexIntersection() {
    qh = qt = 0;
    sort(border, border + n);
    n = unique(border, border + n) - border;
    for (int i = 0; i < n; ++i) {
        Border cur = border[i];
        while (qh + 1 < qt && !check(que[qt - 2], que[qt - 1], cur))
            --qt;
        while (qh + 1 < qt && !check(que[qh], que[qh + 1], cur))
            ++qh;
        que[qt++] = cur;
    }
    while (qh + 1 < qt && !check(que[qt - 2], que[qt - 1], que[qh]))
        --qt;
    while (qh + 1 < qt && !check(que[qh], que[qh + 1], que[qt - 1]))
        ++qh;
}

double calcArea() {
    static Point ps[MAX_N_BORDER];
    int cnt = 0;

    if (qt - qh <= 2) {
        return 0;
    }

    for (int i = qh; i < qt; ++i) {
        int next = i + 1 == qt ? qh : i + 1;
        ps[cnt++] = isBorder(que[i], que[next]);
    }

    double area = 0;
    for (int i = 0; i < cnt; ++i) {
        area += ps[i].det(ps[(i + 1) % cnt]);
    }
    area /= 2;
    area = fabsl(area);
    return area;
}

double halfPlaneIntersection(vector<Line> cur) {
    n = 0;
    for (auto i: cur)
        add(i[0].x, i[0].y, i[1].x, i[1].y);
    convexIntersection();
    return calcArea();
}
} // namespace sjtu

const double INF = 100;
const double EPS = 1e-8;
void addInf(vector<Line> &res, double INF = INF) {
    vector<P> infPts({P(INF, INF), P(-INF, INF), P(-INF, -INF), P(INF, -INF)});
    for (int i = 0; i < 4; i++)
        res.push_back({infPts[i], infPts[(i + 1) % 4]});
}
P randPt(int lim = INF) { return P(rand() % lim, rand() % lim); }
void test1() {
    vector<Line> t({{P(0, 0), P(5, 0)}, {P(5, -2), P(5, 2)}, {P(5, 2), P(2, 2)}, {P(0, 3), P(0, -3)}});
    auto res = halfPlaneIntersection(t);
    assert(polygonArea2(res) == 20);
    addInf(t);
    res = halfPlaneIntersection(t);
    assert(polygonArea2(res) == 20);
}
void testInf() {
    vector<Line> t({{P(0, 0), P(5, 0)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(polygonArea2(res) / (4 * INF * INF) == 1);
    t = vector<Line>({{P(0, 0), P(5, 0)}, {P(0, 0), P(0, 5)}});
    addInf(t);
    res = halfPlaneIntersection(t);
    assert(polygonArea2(res) / (2 * INF * INF) == 1);
}
void testLine() {
    vector<Line> t({{P(0, 0), P(5, 0)}, {P(5, 0), P(0, 0)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(sz(res) >= 2);
    assert(polygonArea2(res) == 0);
}
void testPoint() {
    vector<Line> t({{P(0, 0), P(5, 0)}, {P(5, 0), P(0, 0)}, {P(0, 0), P(0, 5)}, {P(0, 5), P(0, 0)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(sz(res) >= 1);
    assert(polygonArea2(res) == 0);
}
void testEmpty() {
    vector<Line> t(
        {{P(0, 0), P(5, 0)}, {P(5, 0), P(0, 0)}, {P(0, 0), P(0, 5)}, {P(0, 5), P(0, 0)}, {P(0, 2), P(5, 2)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(sz(res) == 0);
}
void testRandom() {
    int lim = 10;
    for (int i = 0; i < 1000; i++) {
        vector<Line> t;
        for (int i = 0; i < 6; i++) {
            Line cand{P(0, 0), P(0, 0)};
            while (cand[0] == cand[1])
                cand = {randPt(lim), randPt(lim)};
            t.push_back(cand);
        }
        addInf(t, lim);
        auto res = halfPlaneIntersection(t);
        double area = sjtu::halfPlaneIntersection(t);
        double diff = abs(2 * area - polygonArea2(res));
        if (diff > EPS) {
            cout << diff << ' ' << area << ' ' << endl;
            for (auto i : t)
                cout << i[0] << "->" << i[1] << ' ';
            cout << endl;
            for (auto i : res)
                cout << i << ',';
            cout << endl;
        }
        assert(diff < EPS);
    }
}

int main() {
    test1();
    testInf();
    testLine();
    testPoint();
    testEmpty();
    testRandom();
    // Failure case for MIT
    // vector<Line> t({{P(9, 8), P(9, 1)}, {P(3, 3), P(3, 5)}, {P(7, 6), P(0, 8)}});
    // addInf(t);
    // cout << polygonArea2(halfPlaneIntersection(t)) << endl;
    // cout << MIT::Intersection_Area(convert(t)) << endl;
    cout << "Tests passed!" << endl;
}
