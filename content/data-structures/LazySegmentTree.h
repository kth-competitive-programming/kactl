/**
 * Author: FHVirus
 * Date: 2023-08-29
 * License: CC0
 * Source: ac-library & https://omeletwithoutegg.github.io/2019/12/07/Iterative-SegmentTree/
 * Description: ZKW implementation with ACL style nodes. [l, r).
 * Time: O(N + Q \log N).
 * Usage: SGT<Val, Tag> sgt(n);
 * Status: tested @ yosupo/range_affine_range_sum
 */
#pragma once

struct Val {
  Val() {} // must return identity element   
  Val operator + (const Val& o) const {}
  // merge two Vals, order is important
};
struct Tag {
  Tag() {} // must return identity element
  Tag operator + (const Tag& o) const {}
  // compose two Tags, order is important
  Val operator() (Val v) const {}
  // apply the Tag to v
};

int bc(int u) { return u <= 1 ? 1 : (2 << __lg(u-1)); }
template <class V, class T> struct SGT {
  int n; vector<V> val; vector<T> tag;
  SGT(int n): n(bc(n)), val(n*2), tag(n*2) {}
  SGT(const vector<V>& v): n(bc(sz(v))), val(n*2), tag(n*2) {
    rep (i, 0, sz(v)) val[i+n] = v[i];
    for (int i = n; --i; ) val[i] = val[i*2] + val[i*2+1];
  }
  void upd(int u, T t)
  { val[u] = t(val[u]); if (u < n) tag[u] = tag[u] + t; }
  void pull(int u)
  { while (u /= 2) val[u] = tag[u](val[u*2] + val[u*2+1]); }
  void push(int u) {
    for (int h = __lg(n)+1, i; --h;) {
      i = u >> h;
      upd(i * 2, tag[i]);
      upd(i * 2 + 1, tag[i]);
      tag[i] = T();
    }
  }
  void set(int p, V v)
  { push(p += n); val[p] = v; pull(p); }
  V query(int l, int r) {
    V rl, rr;
    for (push(l+=n), push((r+=n)-1); l < r; l /= 2, r /= 2) {
      if (l & 1) rl = rl + val[l++];
      if (r & 1) rr = val[--r] + rr;
    }
    return rl + rr;
  }
  void modify(int l, int r, T t) {
    int tl = (l += n), tr = (r += n) - 1;
    for (push(tl), push(tr); l < r; l >>= 1, r >>= 1) {
      if (l & 1) upd(l++, t);
      if (r & 1) upd(--r, t);
    }
    pull(tl); pull(tr);
  }
};
