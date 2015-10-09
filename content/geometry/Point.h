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

#define R(x) const { return x; }
template <class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) R(x<p.x || (x==p.x && y<p.y))
	bool operator==(P p) R(x==p.x && y==p.y)
	P operator+(P p) R(P(x+p.x, y+p.y))
	P operator-(P p) R(P(x-p.x, y-p.y))
	P operator*(T d) R(P(x*d, y*d))
	P operator/(T d) R(P(x/d, y/d))
	T dot(P p) R(x*p.x + y*p.y)
	T cross(P p) R(x*p.y - y*p.x)
	T dist2() R(x*x + y*y) // distance^2
	double dist() R(sqrt((double)dist2())) //length
	// angle to x-axis in interval [-pi, pi]
	double angle() R(atan2(y, x))
	P unit() R(*this/(T)dist()) // makes dist()=1
	P perp() R(P(-y, x)) // rotates +pi/2 radians
	P normal() R(perp().unit())
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) R(P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)))
};
