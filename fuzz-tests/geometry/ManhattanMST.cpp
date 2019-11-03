#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


#include "../../content/geometry/Point.h"
#include "../../content/geometry/ManhattanMST.h"
#include "../../content/data-structures/UnionFind.h"


typedef Point<int> P;
double rectilinear_mst_n(vector<P> ps) {
  struct edge { int src, dst; double weight; };
  vector<edge> edges;

  auto dist = [&](int i, int j) {
    return abs((ps[i]-ps[j]).x) + abs((ps[i]-ps[j]).y);
  };
  for (int i = 0; i < ps.size(); ++i)
    for (int j = i+1; j < ps.size(); ++j)
      edges.push_back({i, j, dist(i,j)});
  double cost = 0;
  sort(all(edges), [](edge a, edge b) { return a.weight < b.weight; });
  UF uf(ps.size());
  for (auto e: edges)
    if (uf.join(e.src, e.dst))
      cost += e.weight;
  return cost;
}

signed main() {
    for (int t=0; t<100; t++) {
        int num_pts = 1000;
        vector<P> pts;
        for (int i = 0; i < num_pts; ++i) {
            double x = rand() % 300;
            double y = rand() % 300;
            pts.push_back(P(x,y));
        }
        auto edges = manhattanMST(pts);
        sort(all(edges));
        UF uf(sz(pts));
        int cost = 0;
        for (auto e: edges) if (uf.join(e[1], e[2])) cost += e[0];
        assert(cost == rectilinear_mst_n(pts));
    }

}