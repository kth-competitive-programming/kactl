/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: Sphere volume and angle normalization.
 */
class GeometryUtils {
  double epsilon = 1e-8;

  double sphereVolume(double radius) {
    return 4 * PI * radius * radius * radius / 3;
  }

  double canonicalAngle(double angle) {
    while (angle > +PI) angle -= 2 * PI;
    while (angle < -PI) angle += 2 * PI;
    return angle;
  }

  double positiveAngle(double angle) {
    while (angle > 2 * PI - epsilon) angle -= 2 * PI;
    while (angle < -epsilon) angle += 2 * PI;
    return angle;
  }
}
