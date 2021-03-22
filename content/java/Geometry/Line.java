/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Line class.
 */
class Line {
  double a, b, c;
  double b;
  double c;

  Line(Point p, double angle) {
    a = sin(angle);
    b = -cos(angle);
    c = -p.x * a - p.y * b;
  }

  Line(double a, double b, double c) {
    double h = hypot(a, b);
    this.a = a / h;
    this.b = b / h;
    this.c = c / h;
  }

  Point intersect(Line other) {
    if (parallel(other)) return null;
    double determinant = b * other.a - a * other.b;
    double x = (c * other.b - b * other.c) / determinant;
    double y = (a * other.c - c * other.a) / determinant;
    return new Point(x, y);
  }

  boolean parallel(Line other) {
    return abs(a * other.b - b * other.a) < epsilon;
  }

  boolean contains(Point point) {
    return abs(value(point)) < epsilon;
  }

  Line perpendicular(Point point) {
    return new Line(-b, a, b * point.x - a * point.y);
  }

  double value(Point point) {
    return a * point.x + b * point.y + c;
  }

  Point[] intersect(Circle circle) {
    double distance = distance(circle.center);
    if (distance > circle.radius + epsilon)
        return new Point[0];
    Point intersection = intersect(
      perpendicular(circle.center));
    if (abs(distance - circle.radius) < epsilon)
        return new Point[]{intersection};
    double shift = sqrt(
      circle.radius * circle.radius -
      distance * distance);
    return new Point[]{
      new Point(
        intersection.x + shift * b,
        intersection.y - shift * a),
      new Point(
        intersection.x - shift * b,
        intersection.y + shift * a)
    };
  }

  double distance(Point center) { return abs(value(center)); }

  double angle() { return atan2(-a, b); }

  @Override
  public boolean equals(Object o) {
    Line line = (Line) o;
    if (!parallel(line)) return false;
    if (abs(a * line.c - c * line.a) > epsilon ||
        abs(b * line.c - c * line.b) > epsilon)
      return false;
    return true;
  }
}
