/**
 * Author: Ulf Lundstrom with inspiration from tinyKACTL
 * Date: 2009-02-26
 * Source:
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long.
 * Usage:
 * 	Point<doubel> p1(5.1, -3.9), p2;
/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-07
 * Source:
 * Description: returns the shortest distance on the sphere with radius radius between the points with azimuthal angles (longitude) f1 ($\phi_1$) and f2 ($\phi_2$) from x-axis and zenith angles (latitude) t1 ($\theta_1$) and t2 ($\theta_2$) from y-axis. All angles measured in radians.
 * Status: somewhat tested, to be tested with UVa 535
 */
#pragma once
#include <cmath>

double sphericalDistance(double f1, double t1,
		double f2, double t2, double radius) {
	double dx = sin(t2)*cos(f2) - sin(t1)*cos(f1);
	double dy = sin(t2)*sin(f2) - sin(t1)*sin(f1);
	double dz = cos(t2) - cos(t1);
	double d = sqrt(dx*dx+dy*dy+dz*dz);
	return radius*2*asin(d/2);
}
 * 	cin >> p2;
 * 	double distance = (p1*2-p2.rotate(M_PI/3)).dist();
 * 	double area = p1.cross(p2)/2;
 * 	cout << "p1=" << p1;
 * Status: Works fine
 */
#pragma once
#include <cmath>
#include <iostream>
using namespace std;

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
	T dist2() const { return x*x + y*y; } //distance^2
	double dist() const { return sqrt((double)dist2()); } //length
	//angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); } 
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	P perp() const { return P(-y, x); } //rotates +pi/2 radians
	P normal() const { return perp().unit(); }
	//returns point rotated a radians counterclockwise around origo
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));
	}
};
template <class T>
ostream & operator<<(ostream & os, const Point<T> & p) {
	os << "(" << p.x << "," << p.y << ")";
	return os;
}
template <class T>
istream & operator>>(istream & is, Point<T> & p) {
	is >> p.x >> p.y;
	return is;
}
