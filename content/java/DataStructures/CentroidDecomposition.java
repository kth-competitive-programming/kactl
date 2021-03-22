/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Centroid decomposition without saving.
 */
class CentroidDecomposition {
  List<Integer>[] g;
  boolean[] used;
  int[] time;
  int timer;
  int[] size;

  void findCentroid(int v, int size) {
    int p = -1;
    boolean any = true;
    while (any) {
      any = false;
      for (int to : g[v]) {
        if (to != p && !used[to] &&
            getSize(to, -1) > size / 2) {
          p = v;
          v = to;
          any = true;
          break;
        }
      }
      if (!any) break;
    }
    used[v] = true;
    process(v);
    for (int to : g[v]) {
      if (!used[to]) {
        timer++;
        findCentroid(to, getSize(to, -1));
      }
    }
  }

  int getSize(int v, int p) {
    if (time[v] == timer) return size[v];
    time[v] = timer;
    size[v] = 1;
    for (int to : g[v])
      if (to != p && !used[to])
        size[v] += getSize(to, v);
    return size[v];
  }
}
