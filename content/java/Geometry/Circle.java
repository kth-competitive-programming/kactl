/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Cicrle class.
 */
class Circle {
  Point center;
  double radius;

  boolean contains(Point point) {
    return center.distance(point) < radius + epsilon;
  }

  boolean strictContains(Point point) {
    return center.distance(point) < radius - epsilon;
  }

  Point[] findTouchingPoints(Point point) {
    double distance = center.distance(point);
    if (distance < radius - epsilon)
      return new Point[0];
    if (distance < radius + epsilon)
      return new Point[]{point};
    Circle power = new Circle(
      point,
      sqrt((distance - radius) * (distance + radius))
    );
    return intersect(power);
  }

  Point[] intersect(Circle other) {
    double x1 = center.x;
    double y1 = center.y;
    double r1 = radius;
    double x2 = other.center.x;
    double y2 = other.center.y;
    double r2 = other.radius;
    double a = 2 * (x2 - x1);
    double b = 2 * (y2 - y1);
    double c = (x1 * x1 - x2 * x2) +
               (y1 * y1 - y2 * y2) +
               (r2 * r2 - r1 * r1);
    Line line = new Line(a, b, c);
    return line.intersect(this);
  }
  
  double area() {
    return PI * radius * radius;
  }

  double sector(double angle) {
    return area() * angle / (2 * PI);
  }

  double triangle(double angle) {
    return radius * radius * sin(angle) / 2;
  }

  double segment(double angle) {
    return sector(angle) - triangle(angle);
  }
  
  double intersectionArea(Circle other) {
    if (radius > other.radius)
      return other.intersectionArea(this);
    if (center.distance(other.center) + radius <= other.radius)
      return area();
    if (center.distance(other.center) >= radius + other.radius)
      return 0;

    Point[] intersections = intersect(other);
    double angle1 = Point.angle(intersections[0],
                                intersections[1],
                                center);
    double angle2 = Point.angle(intersections[1],
                                intersections[0],
                                other.center);
    if (angle2 > PI) {
        angle1 = 2 * PI - angle1;
        angle2 = 2 * PI - angle2;
    }
    double area1 = segment(angle1);
    double area2 = other.segment(angle2);

    return area1 + area2;
  }
}
