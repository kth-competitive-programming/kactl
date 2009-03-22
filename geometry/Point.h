/**
Provides: Point
Author: Ulf Lundstrom with inspiration from tinyKACTL
Date: 2009-02-26
Description: Class to handle points in the plane.
	T can be e.g. double or long long.
Usage:
	Point<doubel> p1(5.1, -3.9), p2(1, 0);
	double distance = (p1*2-p2.rotate(M_PI/2)).dist();
	double area = p1.cross(p2)/2;
	cout << "p1=" << p1;
Status: Should work fine
*/
#pragma once
#include <cmath>

template <class T>
struct Point {
	typedef T coordType;
	typedef Point P;
	typedef const P & R;
	T x, y;
	explicit Point(T x=T(), T y=T()) : x( x), y( y) { }
	bool operator<(R p) const { return x<p.x || x==p.x && y<p.y; }
	bool operator==(R p) const { return x==p.x && y==p.y; }
	P operator+(R p) const { return P(x+p.x, y+p.y); }
	P operator-(R p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(R p) const { return x*p.x + y*p.y; }
	T cross(R p) const { return x*p.y - y*p.x; }
	T dist2() const { return dot(*this); } //distance^2
	double dist() const { return sqrt(dist2()); }
	//angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); } 
	P unit() const { return *this/(T)dist(); }
	P perp() const { return P(-y, x); } //rotates +pi/2 radians
	P normal() const { return perp().unit(); }
	//returns point rotated a radians counter clock wise around origo
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));
	}
};
template <class T>
ostream & operator<<(ostream & os, Point<T> p) {
	os << "(" << p.x << "," << p.y << ")";
	return os;
}
