/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Bridges finder.
 */
class Bridges {
  List<Integer>[] g;
  boolean[] used;
  int[] tin, fup;
  int timer;

  void dfs(int v, int p) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (int to : g[v]) {
      if (to == p)
        continue;
      if (used[to]) {
        fup[v] = min(fup[v], tin[to]);
      } else {
        dfs(to, v);
        fup[v] = min(fup[v], fup[to]);
        if (fup[to] > tin[v]) process(v, to);
      }
    }
  }

  void findBridges() {
    int n = g.length;
    used = new boolean[n];
    tin = new int[n];
    fup = new int[n];
    timer = 0;
    for (int i = 0; i < n; i++) if (!used[i]) dfs(i, -1);
  }
}
