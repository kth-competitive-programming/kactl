/**
 * Author: EgorKulikov -> Musin
 * Date: 2019-11-26
 * Description: Rational operations.
 */
class Rational implements Comparable<Rational> {
  static final Rational MAX_VALUE = new Rational(MAX_VALUE, 1);
  static final Rational MIN_VALUE = new Rational(MIN_VALUE, 1);
  static final Rational ONE = new Rational(1, 1);
  static final Rational ZERO = new Rational(0, 1);

  long numerator;
  long denominator;

  Rational(long numerator, long denominator) {
    if (denominator == 0)
      throw new IllegalArgumentException();
    long gcd = gcd(abs(numerator), abs(denominator));
    if (denominator > 0) {
      this.numerator = numerator / gcd;
      this.denominator = denominator / gcd;
    } else {
      this.numerator = -numerator / gcd;
      this.denominator = -denominator / gcd;
    }
  }

  int compareTo(Rational other) {
    return compare(numerator * other.denominator,
                   denominator * other.numerator);
  }

  Rational add(Rational other) {
    return new Rational(
      numerator * other.denominator +
      denominator * other.numerator,
      denominator * other.denominator
    );
  }

  Rational reverse() {
    if (numerator == 0)
      throw new ArithmeticException();
    return new Rational(denominator, numerator);
  }

  Rational multiply(long number) {
    return new Rational(numerator * number, denominator);
  }

  Rational subtract(Rational other) {
    return new Rational(
      numerator * other.denominator -
       denominator * other.numerator,
      denominator * other.denominator
    );
  }

  @Override
  public boolean equals(Object o) {
    Rational rational = (Rational) o;
    if (denominator != rational.denominator) return false;
    if (numerator != rational.numerator)     return false;
    return true;
  }

  Rational divide(long number) {
    return new Rational(numerator, denominator * number);
  }

  long floor() {
		return numerator >= 0
      ? numerator / denominator
      : (numerator - denominator + 1) / denominator;
  }

  long ceil() {
    return numerator >= 0
      ? (numerator + denominator - 1) / denominator
      : numerator / denominator;
  }

  Rational divide(Rational other) {
    return new Rational(numerator * other.denominator,
                        other.numerator * denominator);
  }

  Rational multiply(Rational other) {
    return new Rational(numerator * other.numerator,
                        other.denominator * denominator);
  }

  double value() {
    return (double) numerator / denominator;
  }

  Rational abs() {
    if (numerator >= 0) return this;
    return new Rational(-numerator, denominator);
  }
}
