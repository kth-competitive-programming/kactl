/**
 * Author:
 * Description:
 * Status: tested by one problem
 */
#pragma once

struct Fraction {
    __int128 a, b;
    Fraction() {}
    Fraction(__int128 _a, __int128 _b): a(_a), b(_b) {
        if (b < 0) a = -a, b = -b;
        __int128 d = gcd(a, b);
        a /= d, b /= d;
    }
    bool operator==(const Fraction& r) const { return a * r.b == b * r.a; }
    bool operator<(const Fraction& r) const { return a * r.b < b * r.a; }
    bool operator>(const Fraction& r) const { return a * r.b > b * r.a; }
    bool operator>=(const Fraction& r) const { return a * r.b >= b * r.a; }
    Fraction operator*(const Fraction& x) const { return Fraction(a*x.a, b*x.b); }
    Fraction operator-() const { return Fraction{-a, b}; }
    Fraction operator+(const Fraction& r) const { return Fraction(a*r.b+b*r.a, b*r.b); }
    Fraction operator-(const Fraction& r) const { return Fraction(a*r.b-b*r.a, b*r.b); }
};

ostream& operator<<(ostream& os, Fraction& x) { os << '(' << (ll)x.a << ' ' << (ll)x.b << ')'; return os; }
