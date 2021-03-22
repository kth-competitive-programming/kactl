/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Makes angle lie in [0..2PI).
 */
double positiveAngle(double angle) {
  while (angle > 2 * PI - epsilon) angle -= 2 * PI;
  while (angle < -epsilon) angle += 2 * PI;
  return angle;
}
