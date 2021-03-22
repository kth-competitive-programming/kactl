/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Point class.
 */
class Point {
  double x, y;

  Line line(Point other) {
    if (equals(other)) return null;
    double a = other.y - y;
    double b = x - other.x;
    double c = -a * x - b * y;
    return new Line(a, b, c);
  }

  double angle() { return atan2(y, x); }

  Point rotate(double angle) {
    double sin = sin(angle);
    double cos = cos(angle);
    double nx = x * cos - y * sin;
    double ny = x * sin + y * cos;
    return new Point(nx, ny);
  }
}
