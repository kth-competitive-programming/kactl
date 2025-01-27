/**
 * Author: Tyler Marks
 * Date: 2024-04-29
 * Source: derived from random codeforces blog
 * Description: Computes all faces of the 3-dimension hull of a point set.
 *  *No four points must be coplanar*, or else random results will be returned.
 *  All faces will point outwards.
 * Time: O(n^2)
 * Status: tested on SPOJ CH3D
 */
#pragma once

#include "Point3D.h"

typedef Point3D<double> P;
const double eps = 1e-6;

vector<array<int, 3>> convex_shell(vector<P> &p) {
	int n = sz(p);
	if(n < 3) return {};
	vector<array<int, 3>> faces;

	vvi active(n, vi(n, false));

	auto add_face = [&](int a, int b, int c) -> void {
		faces.push_back({a, b, c});
		active[a][b] = active[b][c] = active[c][a] = true;
	};

	add_face(0, 1, 2);
	add_face(0, 2, 1);

	rep(i, 3, n) {
		vector<array<int, 3>> new_faces;
		for(auto [a, b, c]: faces)
			if((p[i] - p[a]).dot(p[a].cross(p[b], p[c])) > eps)
				active[a][b] = active[b][c] = active[c][a] = false;
			else new_faces.push_back({a, b, c});
		faces.clear();
		for(array<int, 3> f: new_faces)
			rep(j, 0, 3) if(!active[f[(j+1)%3]][f[j]])
				add_face(f[(j+1)%3], f[j], i);
		faces.insert(end(faces), all(new_faces));
	}

	return faces;
}