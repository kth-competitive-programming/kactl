#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/geometry/Point.h"
#include "../../content/geometry/sideOf.h"
#include "../../content/geometry/PolygonArea.h"
#include "../../content/geometry/PolygonUnion.h"
#include "../utilities/genPolygon.h"
#include "../utilities/random.h"

namespace blackhorse {

using db = double;
const db eps = 1e-8;

struct pt {
    db x, y;
    pt(db x = 0, db y = 0) : x(x), y(y) {}
};

inline int sgn(db x) { return (x > eps) - (x < -eps); }

pt operator-(pt p1, pt p2) { return pt(p1.x - p2.x, p1.y - p2.y); }

db vect(pt p1, pt p2) { return p1.x * p2.y - p1.y * p2.x; }

db scal(pt p1, pt p2) { return p1.x * p2.x + p1.y * p2.y; }

db polygon_union(vector<pt> poly[], int n) {
    auto ratio = [](pt A, pt B, pt O) {
        return !sgn(A.x - B.x) ? (O.y - A.y) / (B.y - A.y) : (O.x - A.x) / (B.x - A.x);
    };
    db ret = 0;
    for (int i = 0; i < n; ++i) {
        for (size_t v = 0; v < poly[i].size(); ++v) {
            pt A = poly[i][v], B = poly[i][(v + 1) % poly[i].size()];
            vector<pair<db, int>> segs;
            segs.emplace_back(0, 0), segs.emplace_back(1, 0);
            for (int j = 0; j < n; ++j)
                if (i != j) {
                    for (size_t u = 0; u < poly[j].size(); ++u) {
                        pt C = poly[j][u], D = poly[j][(u + 1) % poly[j].size()];
                        int sc = sgn(vect(B - A, C - A)), sd = sgn(vect(B - A, D - A));
                        if (!sc && !sd) {
                            if (sgn(scal(B - A, D - C)) > 0 && i > j) {
                                segs.emplace_back(ratio(A, B, C), 1), segs.emplace_back(ratio(A, B, D), -1);
                            }
                        } else {
                            db sa = vect(D - C, A - C), sb = vect(D - C, B - C);
                            if (sc >= 0 && sd < 0)
                                segs.emplace_back(sa / (sa - sb), 1);
                            else if (sc < 0 && sd >= 0)
                                segs.emplace_back(sa / (sa - sb), -1);
                        }
                    }
                }
            sort(segs.begin(), segs.end());
            db pre = min(max(segs[0].first, 0.0), 1.0), now, sum = 0;
            int cnt = segs[0].second;
            for (size_t j = 1; j < segs.size(); ++j) {
                now = min(max(segs[j].first, 0.0), 1.0);
                if (!cnt)
                    sum += now - pre;
                cnt += segs[j].second;
                pre = now;
            }
            ret += vect(A, B) * sum;
        }
    }
    return ret / 2;
}
} // namespace blackhorse

namespace approximate {
#include "../../content/geometry/InsidePolygon.h"
double polygonUnion(vector<vector<P>> &polygons, int lim) {
    int cnt = 0;
    int total = 0;
    for (double y = -lim + 1e-5; y < lim; y += lim / 500.0) {
        for (double x = -lim + 1.1e-5; x < lim; x += lim / 500.0) {
            total++;
            for (auto &i : polygons) {
                if (inPolygon(i, P(x, y))) {
                    cnt++;
                    break;
                }
            }
        }
    }
    return lim * lim * 4 * cnt / double(total);
}
} // namespace approximate

namespace lovelive {
#define re real
#define im imag
#define pb push_back
#define fir first
#define sec second
typedef double db;
const db pi = acos(db(-1));
inline int sgn(db x) { return (x > 1e-8) - (x < -1e-8); }

typedef complex<db> cpoi;
db polygon_union(vector<cpoi> py[], int n) {
    auto ratio = [](cpoi &a, cpoi &b, cpoi &c) {
        cpoi x = b - a, y = c - a;
        if (sgn(re(x)) == 0)
            return im(y) / im(x);
        return re(y) / re(x);
    };
    db ret = 0;
    for (int i = 0; i < n; ++i)
        for (size_t v = 0; v < py[i].size(); ++v) {
            cpoi a = py[i][v], b = py[i][(v + 1) % py[i].size()];
            vector<pair<db, int>> segs = {{0, 0}, {1, 0}};
            for (int j = 0; j < n; ++j)
                if (i != j)
                    for (size_t u = 0; u < py[j].size(); ++u) {
                        cpoi c = py[j][u], d = py[j][(u + 1) % py[j].size()];
                        int sc = sgn(im(conj(b - a) * (c - a)));
                        int sd = sgn(im(conj(b - a) * (d - a)));
                        if (!sc && !sd) {
                            if (sgn(re(conj(b - a) * (d - c))) > 0 && i > j) {
                                segs.pb({ratio(a, b, c), +1});
                                segs.pb({ratio(a, b, d), -1});
                            }
                        } else {
                            db sa = im(conj(d - c) * (a - c));
                            db sb = im(conj(d - c) * (b - c));
                            if (sc >= 0 && sd < 0)
                                segs.pb({sa / (sa - sb), 1});
                            else if (sc < 0 && sd >= 0)
                                segs.pb({sa / (sa - sb), -1});
                        }
                    }
            sort(segs.begin(), segs.end());
            db pre = min(max(segs[0].fir, 0.0), 1.0);
            db cur, sum = 0;
            int cnt = segs[0].sec;
            for (size_t j = 1; j < segs.size(); ++j) {
                cur = min(max(segs[j].fir, 0.0), 1.0);
                if (!cnt)
                    sum += cur - pre;
                cnt += segs[j].sec;
                pre = cur;
            }
            ret += im(conj(a) * b) * sum;
        }
    ret = abs(ret) * 0.5;
    return ret;
}
} // namespace lovelive

P randPt(int lim) { return P(randRange(-lim, lim), randRange(-lim, lim)); }

P rndUlp(int lim, long long ulps = 5) { return P(randNearIntUlps(lim, ulps), randNearIntUlps(lim, ulps)); }

P rndEps(int lim, double eps) { return P(randNearIntEps(lim, eps), randNearIntEps(lim, eps)); }

void testRandom(int n, int numPts = 10, int lim = 5, bool brute = false) {
    vector<vector<P>> polygons;
    for (int i = 0; i < n; i++) {
        vector<P> pts;
        int k = randIncl(3, numPts);
        for (int j = 0; j < k; j++) {
            pts.push_back(randPt(lim)); // rndEps(lim, 1e-10));
        }
        polygons.push_back(genPolygon(pts));
        if (polygonArea2(polygons.back()) < 0) {
            reverse(all(polygons.back()));
        }
    }
    auto val1 = polyUnion(polygons);
    vector<vector<blackhorse::pt>> polygons2;
    for (auto i : polygons) {
        vector<blackhorse::pt> t;
        for (auto j : i)
            t.push_back({j.x, j.y});
        polygons2.push_back(t);
    }
    vector<vector<lovelive::cpoi>> polygons3;
    for (auto i : polygons) {
        vector<lovelive::cpoi> t;
        for (auto j : i)
            t.push_back({j.x, j.y});
        polygons3.push_back(t);
    }
    auto val3 = blackhorse::polygon_union(polygons2.data(), sz(polygons2));
    auto val4 = lovelive::polygon_union(polygons3.data(), sz(polygons3));
    if (abs(val1 - val3) > 1e-8 || abs(val1 - val4) > 1e-8) {
        rep(i, 0, n) {
            for (auto &x : polygons[i]) {
                cout << x << ' ';
            }
            cout << endl;
        }
        abort();
    }
}

int main() {
    // int s = (int)time(0);
    int s = 1;
    // cout << "seed " << s << endl;
    srand(s);
    for (int i = 0; i < 100; i++) {
        testRandom(2, 5, 5);
    }
    for (int i = 0; i < 100; i++) {
        testRandom(2, 10, 2);
    }
    for (int i = 0; i < 50; i++) {
        testRandom(5, 100, 5);
    }
    cout << "Tests passed!" << endl;
}
