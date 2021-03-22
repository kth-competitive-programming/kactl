/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Segment class.
 */
class Segment {
  Point a;
  Point b;

  Segment(Point a, Point b) {
    this.a = a;
    this.b = b;
  }

  double length() { return a.distance(b); }

  double distance(Point point) {
    double length = length();
    double left = point.distance(a);
    if (length < epsilon) return left;
    double right = point.distance(b);
    if (left * left > right * right + length * length)
      return right;
    if (right * right > left * left + length * length)
      return left;
    return point.distance(line());
  }

  Point intersect(Segment other, boolean includeEnds) {
    Line line = line();
    Line otherLine = other.a.line(other.b);
    if (line.parallel(otherLine)) return null;
    Point intersection = line.intersect(otherLine);
    if (contains(intersection, includeEnds) &&
        other.contains(intersection, includeEnds)) {
      return intersection;
    }
    return null;
  }

  boolean contains(Point point, boolean includeEnds) {
    if (a.equals(point) || b.equals(point)) return includeEnds;
    if (a.equals(b)) return false;
    Line line = line();
    if (!line.contains(point)) return false;
    Line perpendicular = line.perpendicular(a);
    double aValue = perpendicular.value(a);
    double bValue = perpendicular.value(b);
    double pointValue = perpendicular.value(point);
    return (aValue < pointValue && pointValue < bValue) ||
           (bValue < pointValue && pointValue < aValue);
  }

  Line line() {
    return a.line(b);
  }

  Point middle() {
    return new Point((a.x + b.x) / 2,
                     (a.y + b.y) / 2);
  }

  Point[] intersect(Circle circle) {
    Point[] result = line().intersect(circle);
    if (result.length == 0) return result;
    if (result.length == 1)
      return contains(result[0], true) ? result : new Point[0];
    if (contains(result[0], true))
      return contains(result[1], true)
        ? result
        : new Point[]{result[0]};
    if (contains(result[1], true))
      return new Point[]{result[1]};
    return new Point[0];
  }

  Point intersect(Line line) {
    Line selfLine = line();
    Point intersection = selfLine.intersect(line);
    if (intersection == null) return null;
    if (contains(intersection, true)) return intersection;
    return null;
  }

  double distance(Segment other) {
    Line line = line();
    Line otherLine = other.line();
    Point p = line == null || otherLine == null
      ? null
      : line.intersect(otherLine);
    if (p != null &&
        contains(p, true) &&
        other.contains(p, true))
      return 0;
    return min(
      min(other.distance(a), other.distance(b)),
      min(distance(other.a), distance(other.b)));
  }
}
