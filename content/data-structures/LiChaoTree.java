/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Li Chao (segment) Tree.
 */
class LiChaoTree {
  Line[] tree;
  int n;

  LiChaoTree(int size) {
    n = Math.max(1, Integer.highestOneBit(size - 1) << 1);
    tree = new Line[2 * n];
    Arrays.fill(tree, new Line(-1, 0, (long) 1e18));
  }

  void add(Line line) { add(1, 0, n - 1, line); }

  void add(int v, int tl, int tr, Line line) {
    if (tl == tr) {
      if (line.value(tl) < tree[v].value(tl)) tree[v] = line;
      return;
    }
    int tm = tl + tr >> 1;
    int signLeft = Long.compare(tree[v].value(tl), line.value(tl));
    int signMid  = Long.compare(tree[v].value(tm), line.value(tm));
    if (signLeft == signMid || signLeft == 0 || signMid == 0) {
      int x = signLeft == 0 ? tl + 1 : tl;
      Line lower = line.value(x) <= tree[v].value(x) ? line : tree[v];
      Line other = lower == line ? tree[v] : line;
      tree[v] = lower;
      add(v * 2 + 1, tm + 1, tr, other);
    } else {
      Line lower = line.value(tr) <= tree[v].value(tr) ? line : tree[v];
      Line other = lower == line ? tree[v] : line;
      tree[v] = lower;
      add(v * 2, tl, tm, other);
    }
  }

  Line getLowest(int x) { return getLowest(1, 0, n - 1, x); }

  Line getLowest(int v, int tl, int tr, int x) {
    if (tl == tr) return tree[v];
    int tm = tl + tr >> 1;
    Line res = x <= tm
      ? getLowest(v * 2, tl, tm, x)
      : getLowest(v * 2 + 1, tm + 1, tr, x);
    if (tree[v].value(x) < res.value(x)) res = tree[v];
    return res;
  }
}
