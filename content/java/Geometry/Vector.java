/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Vector class (do we need it?).
 */
class Vector {
  Point point;

  Vector(Point from, Point to) {
    this(to.x - from.x, to.y - from.y);
  }

  double angleTo(Vector other) {
    return canonicalAngle(other.point.angle() - point.angle());
  }

  double length() { return point.value(); }

  double angle() { return point.angle(); }
}
