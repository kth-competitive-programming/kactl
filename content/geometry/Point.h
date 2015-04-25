/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
#pragma once
#include <cmath>
#include <iostream>
using namespace std;

template <class T>
struct Point {
	typedef Point P;
	typedef const P& R;
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
	//returns point rotated 'a' radians counterclockwise around origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));
	}
};
