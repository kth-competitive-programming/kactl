/**
 * Author: Musin
 * Source: https://codeforces.com/blog/entry/17023
 * Date: 2019-11-26
 * Description: Fast max bipartite matching.
 */
class MaxMatchingInBipartiteGraph {
  int n;
  List<Integer>[] g;
  int[] parent;
  int[] pair;
  boolean[] used;

  boolean dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int to : g[v]) {
      if (parent[to] == -1) {
        pair[v] = to;
        parent[to] = v;
        return true;
      }
    }
    for (int to : g[v]) {
      if (dfs(parent[to])) {
        pair[v] = to;
        parent[to] = v;
        return true;
      }
    }
    return false;
  }

  void run() {
    fill(pair, -1);
    fill(parent, -1);
    for (boolean run = true; run; ) {
      run = 0;
		  fill(used, false);
		  for (int i = 0; i < n; i++)
		    if (pair[i] == -1 && dfs(i)) run = true;
    }
  }
}
