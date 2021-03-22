/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: LIS with binary search.
 */
class LongestIncreasingSubsequenceWithBinarySearch {
  int[] find(int[] a) {
    int n = a.length;
    int[] d = new int[n + 1];
    int[] parent = new int[n];
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
      int l = 0;
      int r = maxLen + 1;
      while (r - l > 1) {
        int m = l + r >> 1;
        if (a[d[m]] < a[i]) l = m;
        else r = m;
      }
      if (r == maxLen + 1 || a[d[r]] > a[i])
        d[r] = i;
      parent[i] = l == 0 ? -1 : d[l];
      maxLen = max(maxLen, r);
    }
    int[] res = new int[maxLen];
    for (int i = 0, at = d[maxLen]; i < maxLen; i++) {
      res[maxLen - i - 1] = at;
      at = parent[at];
    }
    return res;
  }
}
