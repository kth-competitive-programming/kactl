/**
 * Author: André Susano Pinto
 * Date:
 * Source: My other KATCL
 * Description: Calculates the max diameter of a polygon. L is the convex hull and i is the index of separation betwwen the upper and lower hull.
 * Status: Not tested.
 */
#pragma once
#include "Point.h"

template<class TYPE>
TYPE PolygonDiameter( vector<Point> L, int i ) {
	reverse( L.begin()+i , L.end() );
	L.push_back( L[i-1] ); //duplicates the last point of lower hull.
	TYPE dist = -1;
	int j = i - 1 , m = L.size()-1;
	while ( i < m || j > 0 ) {
		dist = max( dist , sq_distance( L[i] , L[j] ) );		
		if  (i == m)	 j--;
		else if (j == 0) i++;
		else if ((L[i+1].y-L[i].y)*(L[j].x-L[j-1].x) > (L[j].y-L[j-1].y)*(L[i+1].x-L[i].x))
				i++;
			else
				j--;
	}
	return dist;  // returns square distance.
}
