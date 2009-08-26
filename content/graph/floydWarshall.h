/**
 * Author: Håkan Terelius
 * Date: 2009-08-26
 * Source: http://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
 * Description: Calculates all-pairs shortest path in a directed graph that might have negative edge distances. Returns true if negative-distance cycles exist. Input is an adjacency matrix where $path[i][j]$ is the weight between vertice $i$ and $j$, or $\infty$ if they aren't adjacent, and $N$ is the number of vertices.
 * Time: O(V^3) where V is the number of vertices.
 * Memory: O(1) (given a matrix of size O(V^2) to store the output).
 * Status: Unknown
 * Usage:
 * int path[N][N], adj_matrix[N][N] = ...;
 * memcpy(path, adj_matrix, sizeof(path));
 * if(floydWarshall(path, N)) ...;
 */
#pragma once
#include <algorithm>
using namespace std;

template<class Z>
bool floydWarshall(Z path, int N) {
	for(int k=0;k<N;++k)
		for(int i=0;i<N;++i)
			for(int j=0;j<N;++j)
				path[i][j]=min(path[i][j], path[i][k]+path[k][j]);
	for(int i=0;i<N;++i)
		if(path[i][i]<0) return true;
	return false;
}