/**
Author: Ulf Lundstrom
Date: 2009-03-21
Description: Returns the signed distance between point p and the line containing points s and e. Positive value on left side, negative on right as seen from s towards e. s==e gives nan. P is supposed to be Point<T> where T is e.g. double or long long. It uses products in intermediate steps so watch out for overflow if using int or long long.
Status: Should work fine
*/
#pragma once
#include "Point.h"

template <class P>
double lineDist(const P& s, const P& e, const P& p) {
	return (double)(e-s).cross(p-s)/(e-s).dist();
}
