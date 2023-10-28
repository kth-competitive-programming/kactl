/**
 * Author: ??? from cp-algorithms
 * Date: 2023-10-27
 * License: ???
 * Description: Returns vertices of the Minkowski sum of two convex polygons
 (also a convex polygon).
 * Status: Tested on https://codeforces.com/contest/87/problem/E
 */
template <class T> //lowest vertex first
void reorder_polygon(vector<Point<T>> &P) {
    int pos = 0;
    for(int i = 1; i < sz(P); i++){
        if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

template <class T> //assumes P and Q are ccw
vector<Point<T>> minkowski(vector<Point<T>> P, vector<Point<T>> Q) {
    reorder_polygon(P);
    reorder_polygon(Q);
    P.pb(P[0]); P.pb(P[1]); Q.pb(Q[0]); Q.pb(Q[1]);
    vector<Point<T>> result;
    int i = 0, j = 0;
    while(i < sz(P) - 2 || j < sz(Q) - 2) {
        result.pb(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if(cross >= 0 && i < sz(P) - 2) ++i;
        if(cross <= 0 && j < sz(Q) - 2) ++j;
    }
    return result;
}
