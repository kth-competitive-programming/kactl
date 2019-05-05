/**
 * Author: Johan Sannemo
 * Date: 2017-05-15
 * License: CC0
 * Source: thin air
 * Description: Line-convex polygon intersection. The polygon must be ccw and have no colinear points.
 *  isct(a, b) returns a pair describing the intersection of a line with the polygon:
 *  \begin{itemize*}
 *    \item $(-1, -1)$ if no collision,
 *    \item $(i, -1)$ if touching the corner $i$,
 *    \item $(i, i)$ if along side $(i, i+1)$,
 *    \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$.
 *  \end{itemize*}
 *  In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$.
 *  The points are returned in the same order as the line hits the polygon.
 * Status: fuzz-tested
 * Time: O(N + Q \log n)
 */
#pragma once

#include "Point.h"

template <class F, class Function>
int extremeVertex(const Polygon<F>& poly, Function direction) {
  int n = static_cast<int>(poly.size()), left = 0, leftSgn;
  auto vertexCmp = [&poly, direction](int i, int j) {
    return sgn(ccw(direction(poly[j]), poly[j] - poly[i])); };
  auto isExtreme = [n, vertexCmp](int i, int& iSgn) {
    return (iSgn = vertexCmp(next(i, n), i)) >= 0 && vertexCmp(i, prev(i, n)) < 0; };
  for (int right = isExtreme(0, leftSgn) ? 1 : n; left + 1 < right;) {
    int middle = (left + right) / 2, middleSgn;
    if (isExtreme(middle, middleSgn)) return middle;
    if (leftSgn != middleSgn ? leftSgn < middleSgn
        : leftSgn == vertexCmp(left, middle)) right = middle;
    else left = middle, leftSgn = middleSgn;
  }
  return left;
}

template <class F1, class F2, class F3>
bool stabConvexPolygon(const Line<F1>& line, const Polygon<F2>& poly, Line<F3>& res) {
  assert(line);
  int right = extremeVertex(poly, [&line](const Point<F2>&) { return line.ab; });
  int left = extremeVertex(poly, [&line](const Point<F2>&) { return -line.ab; });
  auto vertexCmp = [&line](const Point<F2>& vertex) {
    return sgn(ccw(line.ab, vertex - line.a)); };
  int rightSgn = vertexCmp(poly[right]), leftSgn = vertexCmp(poly[left]);
  if (rightSgn < 0 || leftSgn > 0) return false;
  auto intersectChain = [&line, &poly, vertexCmp](int first, int last,
                                                  int firstSgn, Point<F3>& res) {
    int n = static_cast<int>(poly.size());
    while (next(first, n) != last) {
      int middle = (first + last + (first < last ? 0 : n)) / 2;
      if (middle >= n) middle -= n;
      if (vertexCmp(poly[middle]) == firstSgn) first = middle;
      else last = middle;
    }
    intersectLines<0, 0, 0, 0>(line, makeLine(poly[first], poly[last]), res);
  };
  intersectChain(left, right, leftSgn, res.a);
  intersectChain(right, left, rightSgn, res.ab);
  res.ab -= res.a;
  return true;
}
