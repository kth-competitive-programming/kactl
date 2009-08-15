/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-11
 * Source: 
 * Description:
 * Time: O(n^2)
 * Memory: O(n)
 * Status: not done
 * Usage:
 */
#pragma once
#include "lineIntersection.h"
#include "circumcircle.h"

template <class It>
pair<T,double> mec(It begin, It end) {
	typedef typename iterator_traits<It>::value_type T;
	double eps = 1e-10;
	//TODO:1 or 2 points
	vector<T> L; //the points limiting the current circle
	L.push_back(*min_element(begin,end));//point on convex hull
	L.push_back(*begin+(L[0]==*begin));//next on convex hull
	for (It i = begin; i != end; ++i) {
		T p = (*i-L[0]).cross(L[1]-L[0]);
		if ((*i == L[0]) && (p>0 || p==0 &&
				(*i-L[0]).dist2()>(L[1]-L[0]).dist2()))
			L[1] = *i;
	}
	while (true) {
		//the line between L[0] and L[1]
		T s = (L[0]+L[1])/2, e = s+(L[0]-L[1]).perp();
		double r2 = (L[0]-s).dist2(); //the current radius^2
		for (It it = begin; it != end; ++it) {
			//the line between *it and L[0]
			T s1 = (*it-L[0])/2, e1 = s1+(*it-L[0]).perp(), x;
			lineIntersection(s1,e1,s,e,x); //x = intersection point
			double a2 = (*it-x).dist2(); //new radius^2
			if (a2 > d2+eps)
				L.resize(2);
			if (a2 >= d2-eps)
				L.push_back(it);
			d2 = max(d2,a2);
		}
		if (L.size() == 2) {
			return make_pair((L[0]+L[1])/2,(L[0]-L[1]).dist());
		}
		while (L.size() > 2) {
			rep(i,0,3) {
				T& m = L[(i+1)%3];
				if ((L[i]-m).dot(L[(i+2)%3]-m) < 0) {//obtuse angle?
					swap(m,L.back()); L.pop_back(); //remove point
					continue;
				}
			}
			return make_pair(ccCenter(L[0],L[1],L[2]),
											ccRadius(L[0],L[1],L[2]));
		}
	}
}
