/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Polygon class (REWRITE CONVEX HULL).
 */
class Polygon {
  Point[] vertices;

  double area() {
    double sum = 0;
    for (int i = 1; i < vertices.length; i++)
      sum += (vertices[i].x - vertices[i - 1].x) *
             (vertices[i].y + vertices[i - 1].y);
    sum += (vertices[0].x - vertices[vertices.length - 1].x) *
           (vertices[0].y + vertices[vertices.length - 1].y);
    return abs(sum) / 2;
  }

  boolean over(Point a, Point b, Point c) {
    return a.x * (b.y - c.y) +
           b.x * (c.y - a.y) +
           c.x * (a.y - b.y) < -epsilon;
  }

  boolean under(Point a, Point b, Point c) {
    return a.x * (b.y - c.y) +
           b.x * (c.y - a.y) +
           c.x * (a.y - b.y) > epsilon;
  }

  Polygon convexHull(Point[] points) {
    if (points.length == 1)
      return new Polygon(points);
    sort(points, new Comparator<Point>() {
      public int compare(Point o1, Point o2) {
        int value = compare(o1.x, o2.x);
        if (value != 0) return value;
        return Double.compare(o1.y, o2.y);
      }
    });
    Point left = points[0];
    Point right = points[points.length - 1];
    List<Point> up = new ArrayList<>();
    List<Point> down = new ArrayList<>();
    for (Point point : points) {
      if (point == left ||
          point == right ||
          !under(left, point, right)) {
        while (up.size() >= 2 && under(
            up.get(up.size() - 2),
            up.get(up.size() - 1),
            point))
          up.remove(up.size() - 1);
        up.add(point);
      }
      if (point == left ||
          point == right ||
          !over(left, point, right)) {
        while (down.size() >= 2 && over(
            down.get(down.size() - 2),
            down.get(down.size() - 1),
            point))
          down.remove(down.size() - 1);
        down.add(point);
      }
    }
    Point[] result = new Point[up.size() + down.size() - 2];
    int index = 0;
    for (Point point : up) result[index++] = point;
    for (int i = down.size() - 2; i > 0; i--)
      result[index++] = down.get(i);
    return new Polygon(result);
  }

  boolean contains(Point point) {
    return contains(point, false);
  }

  boolean contains(Point point, boolean strict) {
    for (Segment segment : sides())
      if (segment.contains(point, true))
        return !strict;
    double totalAngle = canonicalAngle(
      atan2(vertices[0].y - point.y,
            vertices[0].x - point.x) -
      atan2(vertices[vertices.length - 1].y - point.y,
            vertices[vertices.length - 1].x - point.x)
    );
    for (int i = 1; i < vertices.length; i++)
      totalAngle += canonicalAngle(
        atan2(vertices[i].y - point.y,
              vertices[i].x - point.x) -
        atan2(vertices[i - 1].y - point.y,
              vertices[i - 1].x - point.x)
      );
    return abs(totalAngle) > PI;
  }
}
