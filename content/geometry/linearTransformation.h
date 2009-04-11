/**
 * Author: tinykactl, modified by Ulf Lundstrom
 * Date: 2009-04-09
 * Source:
 * Description: Apply the linear transformation (translation, rotation and scaling) which takes line p0-p1 to line q0-q1 to point r. P is intended to be Point<double>.
 * Status: not tested
 */
#pragma once
#include "Point.h"

template <class P>
P linearTransformation(const P& p0, const P& p1,
		const P& q0, const P& q1, const P& r) {
	P dp = p1-p0, dq=q1-q0, num(dp.cross(dq),dp.dot(dq));
	return q0 + P((r-p0).cross(num), (r-p0).dot(num))/dp.dist2();
}
