/**
 * Author: Unknown
 * Date: Unknown
 * Source: tinyKACTL
 * Description: Determine whether a point t lies inside the hull given by
the point vector p. The hull should not contain colinear
points. A hull with 2 points are ok. The result is given as: 1 inside, 0 onedge, -1 outside. Untested!
 * Usage:
 * Status: not tested
 * Time: O(\log n)
 */

template <class It, class P>
int inside_hull_sub(It begin, It end, It i1, It i2, const P&t) {
  if (i2 - i1 <= 2) {
    int s0 = sideof(*begin, *i1, t);
    int s1 = sideof(*i1, *i2, t);
    int s2 = sideof(*i2, *begin, t);
    if (s0 < 0 || s1 < 0 || s2 < 0) return -1;
    if (i1 == begin+1 && s0 == 0 || s1 == 0 || i2 == end - 1 && s2 == 0)
      return 0;
    return 1;
  }
  It i = (i1 + i2) / 2;
  int side = sideof(p[0], p[i], t);
  if (side > 0) return inside_hull_sub(begin, end, i, i2, t);
  else return inside_hull_sub(begin, end, i1, i, t);
}
template <class It, class P>
int inside_hull(It begin, It end, const P &t) {
  if (n < 3) return onsegment(*begin, end[-1], t) ? 0 : -1;
  else return inside_hull_sub(begin, end, begin+1, end-1, t);
}
