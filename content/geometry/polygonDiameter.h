/**
 * Author: André Susano Pinto
 * Date: 2010-11-18
 * Source: My other KACTL
 * Description: Calculates the max diameter of a polygon. L is the convex hull and i is the index of separation betwwen the upper and lower hull.
 * Status: Not tested.
 */
#pragma once
#include <vector>
using namespace std;

template<class T, class P>
T PolygonDiameter( vector<P> L, int i ) {
	reverse( L.begin()+i , L.end() );
	L.push_back( L[i-1] ); //duplicates the last point of lower hull.
	T dist = -1;
	int j = i - 1 , m = L.size()-1;
	while ( i < m || j > 0 ) {
		dist = max( dist , sq_distance( L[i] , L[j] ) );		
		if  (i == m) j--;
		else if (j == 0) i++;
		else if ((L[i+1].y-L[i].y)*(L[j].x-L[j-1].x) > (L[j].y-L[j-1].y)*(L[i+1].x-L[i].x))
			i++;
		else j--;
	}
	return dist;  // returns square distance.
}
