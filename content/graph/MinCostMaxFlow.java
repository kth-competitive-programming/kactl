/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Min cost max flow (ADD FORD BELLMAN).
 */
class MinCostMaxFlow {
  int n, s, t;
  Edge[][] g;

  int[] used;
  int timer;
  int[] phi;
  int[] dist;
  Edge[] parent;
  boolean dijkstra() {
    timer++;
    fill(dist, MAX_VALUE);
    dist[s] = 0;
    parent = new Edge[n];
    while (true) {
      int curV = -1;
      for (int v = 0; v < n; v++)
        if (used[v] != timer &&
            (curV == -1 || dist[v] < dist[curV])) {
          curV = v;
        }
      if (curV == -1) break;
      used[curV] = timer;
      for (Edge e : g[curV]) {
        if (e == null) continue;
        int newDist = phi[e.from] +
                      e.cost -
                      phi[e.to] +
                      dist[curV];
        if (e.capacity - e.flow > 0 && dist[e.to] > newDist) {
          dist[e.to] = newDist;
          parent[e.to] = e;
        }
      }
    }
    return parent[t] != null;
  }

  Result minCostMaxFlow() {
    used = new int[n];
    dist = new int[n];
    parent = new Edge[n];
    phi = new int[n];
    int cost = 0;
    int flow = 0;
    while (dijkstra()) {
      for (int i = 0; i < n; i++)
        if (dist[i] != MAX_VALUE)
          phi[i] += dist[i]; //or just phi[i] = dist[i]
      int minEdge = MAX_VALUE;
      for (Edge e = parent[t]; e != null; e = parent[e.from])
        minEdge = min(minEdge, e.capacity - e.flow);
      for (Edge e = parent[t]; e != null; e = parent[e.from]) {
        cost += e.cost * minEdge;
        e.flow += minEdge;
        e.rev.flow -= minEdge;
      }
      flow += minEdge;
    }
    return new Result(cost, flow);
  }

  class Result { int cost, flow; }

  class Edge {
    int from, to, cost, capacity, flow;
    Edge rev;
  }
}
