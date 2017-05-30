/**
 * Author: Johan Sannemo
 * Date: 2017-03-12
 * License: CC0
 * Source: Wikipedia
 * Description: Calculates the max squared distance of a set of points.
 * Status: Tested.
 */
#pragma once

#include "ConvexHull.h"

vector<pii> antipodal(const vector<P>& S, vi& U, vi& L) {
	vector<pii> ret;
	int i = 0, j = sz(L) - 1;
	while (i < sz(U) - 1 || j > 0) {
		ret.emplace_back(U[i], L[j]);
		if (j == 0 || (i != sz(U)-1 && (S[L[j]] - S[L[j-1]])
					.cross(S[U[i+1]] - S[U[i]]) > 0)) ++i;
		else --j;
	}
	return ret;
}

pii polygonDiameter(const vector<P>& S) {
	vi U, L; tie(U, L) = ulHull(S);
	pair<ll, pii> ans;
	trav(x, antipodal(S, U, L))
		ans = max(ans, {(S[x.first] - S[x.second]).dist2(), x});
	return ans.second;
}
