/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Sparse table for max function.
 */
class MaxSparseTable {
  static final int maxn = (int) 1e5;
  static int[] logs;
  int[][] st;

  MaxSparseTable(int[] a) {
    initLogs();
    int n = a.length;
    int maxLog = 1;
    while (1 << maxLog <= n) maxLog++;
    st = new int[n][maxLog];
    for (int i = n - 1; i >= 0; i--) {
      st[i][0] = a[i];
      for (int log = 1; i + (1 << log) <= n; log++) {
        st[i][log] = max(
          st[i][log - 1],
          st[i + (1 << (log - 1))][log - 1]);
      }
    }
  }

  void initLogs() {
    if (logs != null) return;
    logs = new int[maxn + 1];
    for (int i = 1, log = 0; i <= maxn; i++) {
      if ((1 << (log + 1)) == i) log++;
      logs[i] = log;
    }
  }

  int get(int l, int r) {
    int len = r - l + 1;
    int log = logs[len];
    return max(st[l][log], st[r - (1 << log) + 1][log]);
  }
}
