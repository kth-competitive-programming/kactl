#include "../utilities/template.h"

#include "../../content/geometry/LineProjectionReflection.h"
#include "../../content/geometry/lineDistance.h"

typedef Point<double> P;
int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    const int lim = 5;
    for (int i = 0; i < 100000; i++) {
        P p = P(rand() % lim, rand() % lim);
        P a = P(rand() % lim, rand() % lim);
        P b = P(rand() % lim, rand() % lim);
        while (a == b)
            b = P(rand() % lim, rand() % lim);
        auto proj = lineProj(a, b, p, false);
        auto refl = lineProj(a, b, p, true);
        assert(lineDist(a, b, proj) < 1e-8);
        auto manProj = (refl + p) / 2;
        assert((proj-manProj).dist() < 1e-8);
    }
    cout<<"Tests passed!"<<endl;
}
