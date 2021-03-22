/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Z- and Phi- string functions.
 */
class StringAlgorithms {
  int[] zFunction(char[] s) {
    int n = s.length;
    int[] z = new int[n];
    for (int i = 1, l = 0, r = 0; i < n; i++) {
      if (i <= r) z[i] = min(r - i + 1, z[i - l]);
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
      if (i + z[i] - 1 > r) {
        l = i;
        r = i + z[i] - 1;
      }
    }
    return z;
  }

  int[] prefixFunction(char[] s) {
    int n = s.length;
    int[] pi = new int[n];
    int k = 0;
    for (int i = 1; i < n; i++) {
      while ((k > 0) && (s[k] != s[i])) k = pi[k - 1];
      if (s[k] == s[i]) k++;
      pi[i] = k;
    }
    return pi;
  }

  boolean contains(String s, String target) {
    int[] z = zFunction((target + s).toCharArray());
    for (int i = target.length(); i < z.length; i++)
      if (z[i] >= target.length())
        return true;
    return false;
  }
}
