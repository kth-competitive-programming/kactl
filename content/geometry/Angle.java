/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Angle class.
 */
class Angle {
  Point o, a, b;

  // [0..2PI)
  double value() {
    double x1 = a.x - o.x, y1 = a.y - o.y;
    double x2 = b.x - o.x, y2 = b.y - o.y;
    double scal = x1 * x2 + y1 * y2;  //x(cos)
    double vect = x1 * y2 - x2 * y1;  //y(sin)
    double a = atan2(vect, scal);
    if (a < 0) a += 2 * PI;  //or abs to get a lower angle
    return a;
  }
}
