/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Makes angle lie in [-PI..PI).
 */
double canonicalAngle(double angle) {
  while (angle > +PI) angle -= 2 * PI;
  while (angle < -PI) angle += 2 * PI;
  return angle;
}
