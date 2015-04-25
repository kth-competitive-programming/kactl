/**
 * Author: Ulf Lundstrom with inspiration from tinyKACTL
 * Date: 2009-04-14
 * Source:
 * Description: Class to handle points in 3D space.
 * 	T can be e.g. double or long long.
 * Usage:
 * Status: not tested
 */
#pragma once
#include <cmath>
#include <iostream>
using namespace std;

template <class T>
struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	Point3D(T x, T y, T z) : x(x), y(y), z(z) { }
	bool operator<(R p) const {
		return x<p.x || x==p.x && (y<p.y || y==p.y && z<p.z);
	}
	bool operator==(R p) const { return x==p.x&&y==p.y&&z==p.z; }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
	T dist2() const { return x*x + y*y + z*z; } //distance^2
	double dist() const { return sqrt((double)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	double phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	double theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated a radians ccw around axis
	P rotate(double angle, P axis) const {
		double s = sin(angle), c = cos(angle);
		P u = axis.unit();
		return P((u.x*u.x+(1-u.x*u.x)*c)*x
				+ (u.y*u.x*(1-c)-u.z*s)*y + (y.x*y.z(1-c)+u.y*s)*z,
				(u.x*u.y*(1-c)+u.z*s)*x + (u.y*u.y+(1-u.y*u.y))*y
				+ (u.y*u.z*(1-c)-u.x*s)*z,
				(u.x*u.z*(1-c)-u.y*s)*x + (u.y*u.z*(1-c)+u.x*s)*y
				+ (u.z*u.z+(1-u.z*u.z)*c)*z);
	}
	operator double() const { return dist(); }
};
