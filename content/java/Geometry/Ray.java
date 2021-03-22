/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Ray class.
 */
class Ray {
  Point base;
  Line line;
  Line perpendicular;

  Ray(Point base, double direction) {
    this.base = base;
    line = new Line(base, direction);
    this.perpendicular = line.perpendicular(base);
  }

  Ray(Point base, Point other) {
    this.base = base;
    line = base.line(other);
    this.perpendicular = line.perpendicular(base);
  }

  boolean contains(Point point) {
    return line.contains(point) &&
           perpendicular.value(point) > -epsilon;
  }

  double distance(Point point) {
    if (perpendicular.value(point) > -epsilon)
      return line.distance(point);
    return base.distance(point);
  }
}
