/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Strongle connected components finder.
 */
class StronglyConnectedComponents {
  int n;
  List<Integer>[] g, gr;

  boolean[] used;
  List<Integer> order;
  void dfs1(int v) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++)
      if (!used[g[v].get(i)])
        dfs1(g[v].get(i));
    order.add(v);
  }

  List<Integer> component;
  void dfs2(int v) {
    used[v] = true;
    component.add(v);
    for (int i = 0; i < gr[v].size(); i++)
      if (!used[gr[v].get(i)])
        dfs2(gr[v].get(i));
  }

  void find() {
    used = new boolean[n];
    order = new ArrayList<>();
    for (int i = 0; i < n; ++i) if (!used[i]) dfs1(i);
    fill(used, false);
    component = new ArrayList<>();
    for (int i = 0; i < n; ++i) {
      int v = order.get(n - i - 1);
      if (!used[v]) {
        dfs2(v);
        process();
        component.clear();
      }
    }
  }
}
