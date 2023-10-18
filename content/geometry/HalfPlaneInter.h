/**
 * Author: FHVirus
 * Date: 2023-09-29
 * License: CC0
 * Source: cheissmart & baluteshih (8BQube's codebook)
 * Description: Given n segments (s, t), returns polygon sides
 * representing the intersection of left side of the segments.
 * Status: Tested with Big Brother on Kattis.
 */
#pragma once

#include "Point.h"

template <class P> struct Seg { P s, t; };
template <class S>
bool xleft(const S& o, const S& a, const S& b) {
  auto [o3, o4] = make_pair(o.s.cross(o.t, b.s),
      o.s.cross(o.t, b.t)); // C^2
  auto [a3, a4] = make_pair(a.s.cross(a.t, b.s),
      a.s.cross(a.t, b.t));
  if (a3 - a4 < 0) a3 *= -1, a4 *= -1;
  return (__int128) o4 * a3 - (__int128) o3 * a4 > 0; // C^4
}
template <class P>
int cmp(const P& a, const P& b, const bool same = true) {
  int na = (a < P(0, 0)), nb = (b < P(0, 0));
  if (na != nb) return na < nb;
  if (sgn(a.cross(b)) != 0) return sgn(a.cross(b)) > 0;
  return same ? a.dist2() < b.dist2() : -1;
}
template<class S>
vector<S> halfPlaneInter(vector<S> ss) {
  sort(all(ss), [&](S a, S b) -> int {
    int t = cmp(a.t - a.s, b.t - b.s, 0);
    return (t != -1 ? t : sgn(a.s.cross(a.t, b.s)) < 0);
  });
  int n = sz(ss), qh = 0, qt = 1;
  vector<S> dq(n); dq[0] = ss[0];
  rep(i, 1, n) {
    if ((ss[i-1].t - ss[i-1].s).cross(ss[i].t - ss[i].s) == 0)
      continue;
    while (qt-qh>1 and !xleft(ss[i], dq[qt-2], dq[qt-1])) --qt;
    while (qt-qh>1 and !xleft(ss[i], dq[qh], dq[qh+1])) ++qh;
    dq[qt++] = ss[i];
  }
  while (qt-qh>2 and !xleft(dq[qh], dq[qt-2], dq[qt-1])) --qt;
  return {begin(dq) + qh, begin(dq) + qt};
}
