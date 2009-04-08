/**
Author: Ulf Lundstrom
Date: 2009-04-07
Description: returns the shortest distance on the sphere with radius radius between the points with azimuthal angles f1 ($\phi_1$) and f2 ($\phi_2$) and zenith angles t1 ($\theta_1$) and t2 ($\theta_2$).
Status: somewhat tested, to be tested with UVa 535
Usage:
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
