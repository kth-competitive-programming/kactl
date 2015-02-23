/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * Source: http://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
 * Description: Same as normal floydWarshall. Propagates negative distances.
 * Time: O(V^3) where V is the number of vertices.
 * Status: Working
 */
#pragma once

template <typename T, typename Matrix> void floydWarshall2(Matrix& m, int n, const T& inf, const T& negInf){
	rep(k,0,n)
		rep(i,0,n)
			rep(j,0,n)
				if(m[i][k] != inf && m[k][j] != inf) {
					T newDist = m[i][k] + m[k][j];
					if(m[i][j] == inf || newDist < m[i][j])
						m[i][j] = newDist;
				}
	rep(i,0,n)
		rep(j,0,n)
			for(int k = 0; m[i][j] != negInf && k < n; ++k)
				if(m[i][k] != inf && m[k][j] != inf && (m[k][k] < 0 || m[k][k] == negInf))
					m[i][j] = negInf;
}
