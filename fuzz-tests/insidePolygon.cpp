#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


#include "../content/geometry/SegmentIntersection.h"
namespace oldImpl {
template<class It, class P>
bool insidePolygon(It begin, It end, const P& p,
		bool strict = true) {
	int n = 0; //number of isects with line from p to (inf,p.y)
	for (It i = begin, j = end-1; i != end; j = i++) {
		//if p is on edge of polygon
		if (onSegment(*i, *j, p)) return !strict;
		//or: if (segDist(*i, *j, p) <= epsilon) return !strict;
		//increment n if segment intersects line from p
		n += (max(i->y,j->y) > p.y && min(i->y,j->y) <= p.y &&
				((*j-*i).cross(p-*i) > 0) == (i->y <= p.y));
	}
	return n&1; //inside if odd number of intersections
}

}
typedef Point<double> P;
ostream &operator<<(ostream &os, P p) { return cout << "(" << p.x << "," << p.y << ")"; }
bool eq(P a, P b) {
    return (a-b).dist()<EPS;
}
int main() {
    rep(t,0,100000) {
        const int GRID=5;
        P a(rand()%GRID, rand()%GRID), b(rand()%GRID, rand()%GRID), c(rand()%GRID, rand()%GRID), d(rand()%GRID, rand()%GRID);
        P tmp1, tmp2;
        auto res = oldImpl::segmentIntersection(a,b,c,d, tmp1, tmp2);
        auto res2 = segInter(a,b,c,d);
        if (res != res2.size()) {
            cout<<a<<' '<<b<<' '<<c<<' '<<d<<endl;
            cout<<"old: "<<res<<" new: "<<res2.size()<<endl;
        }
        assert(res==res2.size());
        if (res==1) {
            assert(eq(*res2.begin(), tmp1));
        } else if (res==2) {
            vector<P> a(res2.begin(), res2.end());
            vector<P> b({tmp1, tmp2});
            sort(all(b));
            assert(eq(a[0], b[0]) && eq(a[1],b[1]));
        }
    }
    cout<<"Tests passed!"<<endl;
}
