#include "../utilities/template.h"

#include "../../content/geometry/Point.h"
#include "../../content/geometry/ManhattanMST.h"
#include "../../content/data-structures/UnionFind.h"


typedef Point<int> P;
typedef int T;
T rectilinear_mst_n(vector<P> ps) {
  struct edge { int src, dst; T weight; };
  vector<edge> edges;

  auto dist = [&](int i, int j) {
    return abs((ps[i]-ps[j]).x) + abs((ps[i]-ps[j]).y);
  };
  for (int i = 0; i < sz(ps); ++i)
    for (int j = i+1; j < sz(ps); ++j)
      edges.push_back({i, j, dist(i,j)});
  T cost = 0;
  sort(all(edges), [](edge a, edge b) { return a.weight < b.weight; });
  UF uf(sz(ps));
  for (auto e: edges)
    if (uf.join(e.src, e.dst))
      cost += e.weight;
  return cost;
}

signed main() {
    for (int t=0; t<10000; t++) {
        const int max_coord = rand() % 300 + 1;
        const int num_pts = rand() % 100;
        vector<P> pts;
        for (int i = 0; i < num_pts; ++i) {
            int x = rand() % max_coord - max_coord / 2;
            int y = rand() % max_coord - max_coord / 2;
            pts.push_back(P(x,y));
        }
        auto edges = manhattanMST(pts);
        assert(edges.size() <= 4*pts.size());
        sort(all(edges));
        UF uf(sz(pts));
        int cost = 0, joined = 0;
        for (auto e: edges) if (uf.join(e[1], e[2])) cost += e[0], joined++;
        if (num_pts > 0) assert(joined == num_pts - 1);
        assert(cost == rectilinear_mst_n(pts));
    }
    cout<<"Tests passed!"<<endl;
}
