/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Treap with tree reverse and 
 *  k-th order statistics.
 */
class Treap {
  static Random rnd = new Random(239);
  long priority = rnd.nextLong();
  int size = 1;
  boolean needSwap;
  int value;
  Treap left;
  Treap right;
  Treap parent;

  Treap(int value) {
    this.value = value;
  }

  static Treap merge(Treap t1, Treap t2) {
    update(t1);
    update(t2);
    if (t1 == null) return t2;
    if (t2 == null) return t1;
    if (t1.priority > t2.priority) {
      t1.right = merge(t1.right, t2);
      update(t1);
      return t1;
    } else {
      t2.left = merge(t1, t2.left);
      update(t2);
      return t2;
    }
  }

  static Split split(Treap t, int size) {
    if (t == null) return Split.empty;
    update(t);
    int leftSize = 1 + size(t.left);
    if (leftSize <= size) {
      Split split = split(t.right, size - leftSize);
      t.right = split.left;
      if (split.right != null) split.right.parent = null;
      update(t);
      return new Split(t, split.right);
    } else {
      Split split = split(t.left, size);
      t.left = split.right;
      if (split.left != null) split.left.parent = null;
      update(t);
      return new Split(split.left, t);
    }
  }

  static void reverse(Treap t, int l, int r) {
    int size = r - l + 1;
    Split leftRight = split(t, l);
    Split middleRight = split(leftRight.right, size);
    middleRight.left.needSwap = true;
    update(middleRight.left);
    merge(leftRight.left,
          merge(middleRight.left, middleRight.right));
  }

  static void update(Treap t) {
    if (t == null) return;
    t.size = 1 + size(t.left) + size(t.right);
    if (t.left != null) t.left.parent = t;
    if (t.right != null) t.right.parent = t;
    if (t.needSwap) {
      Treap tmp = t.left;
      t.left = t.right;
      t.right = tmp;
      if (t.left != null) t.left.needSwap ^= true;
      if (t.right != null) t.right.needSwap ^= true;
      t.needSwap = false;
    }
  }

  static void updateTillRoot(Treap t) {
    if (t == null) return;
    updateTillRoot(t.parent);
    update(t);
  }

  int index() {
    updateTillRoot(this);
    int index = size(left);
    for (Treap t = this; t.parent != null; t = t.parent)
      if (t.parent.right == t)
        index += size(t.parent.left) + 1;
    return index;
  }

  static int size(Treap t) { return t == null ? 0 : t.size; }

  static class Split {
    Treap left;
    Treap right;
    static final Split empty = new Split(null, null);
  }
}
