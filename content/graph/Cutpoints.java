/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Cut points finder.
 */
class Cutpoints {
  List<Integer>[] g;
  boolean[] used;
  int[] tin, fup;
  int timer;

  void dfs(int v, int p) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (int to : g[v]) {
      if (to == p) continue;
      if (used[to]) {
        fup[v] = Math.min(fup[v], tin[to]);
      } else {
        dfs(to, v);
        fup[v] = Math.min(fup[v], fup[to]);
        if (fup[to] >= tin[v] && p != -1) process(v);
        children++;
      }
    }
    if (p == -1 && children > 1) process(v);
  }

  void findCutpoints() {
    int n = g.length;
    used = new boolean[n];
    tin = new int[n];
    fup = new int[n];
    timer = 0;
    for (int i = 0; i < n; i++) if (!used[i]) dfs(i, -1);
  }
}
