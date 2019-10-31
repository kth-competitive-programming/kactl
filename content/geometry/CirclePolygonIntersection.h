/**
 * Author: Haobin Ni, chilli
 * Date: 2019-10-31
 * License: CC0
 * Source: https://github.com/FTRobbin/Dreadnought-Standard-Code-Library/blob/master/merge/areaCT.cpp
 * Description: Returns the area of the intersection of a circle with a
 * polygon. areaCT returns the area of the intersection of the triangle
 * (origin, pa, pb) and the circle of radius r with origin at 0.
 * Status: Tested on GNYR 2019 Gerrymandering
 * Time: O(n)
*/
#include "../../content/geometry/Point.h"

typedef Point<double> P;
double areaCT(P pa, P pb, double r) {
    if (pa.dist() < pb.dist()) swap(pa, pb);
    if (sgn(pb.dist()) == 0) return 0;
    double a = pb.dist(), b = pa.dist(), c = (pb - pa).dist();
    double sinB = fabs(pb.cross(pb - pa) / a / c), cosB = pb.dot(pb - pa) / a / c,
           sinC = fabs(pa.cross(pb) / a / b), cosC = pa.dot(pb) / a / b;
    double B = atan2(sinB, cosB), C = atan2(sinC, cosC);
    if (a > r) {
        double S = C / 2 * r * r, h = a * b * sinC / c;
        if (h < r && B < M_PI / 2)
            S -= (acos(h / r) * r * r - h * sqrt(r * r - h * h));
        return S;
    } else if (b > r) {
        double theta = M_PI - B - asin(sinB / r * a);
        return a * r * sin(theta) / 2 + (C - theta) / 2 * r * r;
    } else return sinC * a * b / 2;
}
double circlePoly(P c, double r, vector<P> poly) {
    double area = 0;
    rep(i,0,sz(poly)){
        auto a = poly[i] - c, b = poly[(i+1)%sz(poly)] - c;
        area += areaCT(a, b, r) * sgn(a.cross(b));
    }
    return area;
}