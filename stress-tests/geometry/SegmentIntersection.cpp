#include "../utilities/template.h"

#include "../../content/geometry/SegmentIntersection.h"

namespace oldImpl {
template<class P>
int segmentIntersection(const P& s1, const P& e1,
        const P& s2, const P& e2, P& r1, P& r2) {
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
    r1 = s1-v1*a2/a;
    return 1;
}
}
typedef Point<double> P;
bool eq(P a, P b) {
    return (a-b).dist()<1e-8;
}
int main() {
    rep(t,0,1000000) {
        const int GRID=6;
        P a(rand()%GRID, rand()%GRID), b(rand()%GRID, rand()%GRID), c(rand()%GRID, rand()%GRID), d(rand()%GRID, rand()%GRID);
        P tmp1, tmp2;
        auto res = oldImpl::segmentIntersection(a,b,c,d, tmp1, tmp2);
        auto res2 = segInter(a,b,c,d);
        if (res != sz(res2)) {
            cout<<a<<' '<<b<<' '<<c<<' '<<d<<endl;
            cout<<"old: "<<res<<" new: "<<sz(res2)<<endl;
        }
        assert(res==sz(res2));
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
