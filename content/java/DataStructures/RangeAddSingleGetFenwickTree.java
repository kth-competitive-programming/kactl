/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Fenwick tree with add on segment.
 */
class RangeAddSingleGetFenwickTree {
  int n;
  long[] sum, fun;

  RangeAddSingleGetFenwickTree(int n) {
    this.n = ++n;
    sum = new long[n];
    fun = new long[n];
  }

  void add(int at, long sumValue, long funValue) {
    for (at++; at < n; at += at & -at) {
      sum[at] += sumValue;
      fun[at] += funValue;
    }
  }

  void addConstSegment(int l, int r, long value) {
    add(l, value, 0);
    add(r + 1, -value, 0);
  }

  void addFunctionSegment(int l, int r, long value) {
    add(l, -(l - 1) * value, value);
    add(r + 1, (l - 1) * value, -value);
  }

  long get(int at) {
    int at0 = at;
    long result = 0;
    for (at++; at > 0; at -= at & -at)
        result += sum[at] + fun[at] * at0;
    return result;
  }
}
