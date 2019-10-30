#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// #include "../../content/geometry/PolygonUnionArea.h"

#include "../../content/geometry/Point.h"
#include "../../content/geometry/sideOf.h"
#include "../../content/geometry/PolygonUnionArea.h"
#include "../utilities/genPolygon.h"

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
        for (int v = 0; v < poly[i].size(); ++v) {
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
            for (int j = 1; j < segs.size(); ++j) {
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

void testRandom(int n, int numPts = 10, int lim = 5) {
    vector<vector<P>> polygons;
    for (int i = 0; i < n; i++) {
        vector<P> pts;
        for (int j = 0; j < numPts; j++) {
            pts.push_back(P(rand() % lim, rand() % lim));
        }
        polygons.push_back(genPolygon(pts));
        reverse(all(polygons.back()));
    }
    vector<vector<blackhorse::pt>> polygons2;
    for (auto i : polygons) {
        vector<blackhorse::pt> t;
        for (auto j : i)
            t.push_back({j.x, j.y});
        polygons2.push_back(t);
    }
    auto val1 = polyUnion(polygons);
    auto val2 = blackhorse::polygon_union(polygons2.data(), polygons2.size());
    if (abs(val1 - val2) > 1e-8) {
        cout << val1 << ' ' << val2 << ' ' << endl;
        assert(abs(val1 - val2) < 1e-8);
    }
}
int main() {
    for (int i = 0; i < 1000; i++) {
        testRandom(5, 20, 10);
    }
    for (int i = 0; i < 1000; i++) {
        testRandom(2, 10, 5);
    }
    for (int i = 0; i < 1000; i++) {
        testRandom(5, 100, 10);
    }
}