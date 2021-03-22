/**
 * Author: EgorKulikov -> Musin
 * Date: 2019-11-26
 * Description: Linear C(n,k) and extended euclid (gcd).
 */
class NumericUtils {
  long _x;
  long _y;

  long extGcd(long a, long b) {
    if (a == 0) {
      _x = 0;
      _y = 1;
      return b;
    }
    long d = extGcd(b % a, a);
    long nx = _y - (b / a) * _x;
    _y = _x;
    _x = nx;
    return d;
  }

  int c(int n, int k) {
    double res = 1;
    for (int i = 1; i <= k; i++)
      res = res * (n - k + i) / i;
    return (int) (res + 0.01);
  }
}
