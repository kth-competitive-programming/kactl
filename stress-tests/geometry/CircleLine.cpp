#include "../utilities/template.h"

#include "../../content/geometry/CircleLine.h"

typedef Point<double> P;
int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    {
        auto res = circleLine(P(0, 0), 1, P(-1, -1), P(1, 1));
        assert(res.size() == 2);
        assert((res[1]-P(sqrt(2)/2, sqrt(2)/2)).dist() < 1e-8);
    }
    {
        auto res = circleLine(P(0, 0), 1, P(-5,  1), P(5, 1));
        assert(res.size() == 1);
        assert((res[0]-P(0,1)).dist() < 1e-8);
    }
    {
        auto res = circleLine(P(4, 4), 1, P(0,  0), P(5, 0));
        assert(res.size() == 0);
    }
    cout<<"Tests passed!"<<endl;
}
