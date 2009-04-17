/**
 * Author:
 * Date: 2009-04-17
 * Source: tinyKACTL
 * Description: N/A
 * Status: Unknown
 */
 template <class Z> Z euclid(Z a, Z b, Z &x, Z &y) {
  if (b) {  Z d = euclid(b, a % b, y, x);
            return y -= a/b * x, d;  }
  return x = 1, y = 0, a;
}
