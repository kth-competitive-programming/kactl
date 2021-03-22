/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Flow with restrictions and circulation.
 */
class FlowWithRestrictionsAndCirculation {
  /*
  * Add new S' and T'.
  * For each edge with Li > 0 do:
  * add S'->Bi(Li), add Ai->T'(Li), add Ai->Bi(Ri-Li).
  * Then add T->S(inf).
  *
  * Now run dinic and you're done.
   */
  List<Edge>[] buildGraphWithRestrictions(
      List<Edge0>[] g0, int s0, int t0) {
    int n0 = g0.length;
    int s = n0;
    int t = s + 1;
    int n = n0 + 2;
    List<Edge>[] g = new List[n];
    for (int i = 0; i < n; i++) g[i] = new ArrayList<>();
    for (List<Edge0> adj : g0) {
      for (Edge0 e : adj) {
        addEdge(g, s, e.to, e.min);
        addEdge(g, e.from, t, e.min);
        addEdge(g, e.from, e.to, e.max - e.min);
      }
    }
    //binary search on this to find min flow
    addEdge(g, t0, s0, MAX_VALUE);
    return g;
  }

  /*
  * Make a graph with restrictions and find max flow on it.
  * To find a real flow, add Li to all the edges.
   */
  List<Edge>[] buildCirculation(List<Edge>[] b, int s, int t) {
    return null;
  }

  void addEdge(List<Edge>[] g, int from, int to, int cap) {
    Edge e1 = new Edge(from, to, cap);
    Edge e2 = new Edge(to, from, 0);
    e1.rev = e2;
    e2.rev = e1;
    g[from].add(e1);
    g[to].add(e2);
  }

  class Edge {
    int from, to, capacity;
    Edge rev;   //(to, from, 0)
  }

  class Edge0 { int from, to, min, max; }
}
