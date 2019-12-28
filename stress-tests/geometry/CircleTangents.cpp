#include "../utilities/template.h"

#include "../../content/geometry/CircleTangents.h"
#include "../../content/geometry/lineDistance.h"
#include "../utilities/randGeo.h"

typedef Point<double> P;

signed main() {
    for (int i = 0; i < 1000000; i++) {
        P c1 = randIntPt(5), c2 = randIntPt(5);
        double r1 = sqrt(rand()%20), r2 = sqrt(rand()%20);
        for (auto sgn : {-1, 1}) {
            auto tans = tangents(c1, r1, c2, sgn * r2);

            if (tans.size() ==1) {
                assert((tans[0].first - tans[0].second).dist() < 1e-8);
                assert(abs((tans[0].first-c1).dist() - r1) < 1e-8);
                assert(abs((tans[0].first-c2).dist() - r2) < 1e-8);
            } else if (tans.size() == 2) {
                for (auto l : tans) {
                    assert(abs(abs(lineDist(l.first, l.second, c1))-r1) < 1e-8);
                    assert(abs(abs(lineDist(l.first, l.second, c2))-r2) < 1e-8);
                }
            }
        }
    }
    cout<<"Tests passed!"<<endl;
}
