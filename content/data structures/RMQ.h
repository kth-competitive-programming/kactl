/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * Source: Folklore
 * Status: Tested at Petrozavodsk
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time. 
 * Set inf to something reasonable before use.
 * Usage:
 *  RMQ rmq;
 *  rmq.init(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 */
#pragma once


#include <vector>

using namespace std;

int inf = numeric_limits<int>::max();

template<class T>
struct RMQ {
	vector<vector<T>> jmp;

	void init(vector<T>& V){
		int N = V.size();
		int on = 1, depth = 1;
		while(on < (int)V.size()) on *= 2, depth++;
		jmp.assign(depth, vector<T>(N));
		jmp[0] = V;
		rep(i,0,depth-1) rep(j,0,N)
			jmp[i+1][j] = min(jmp[i][j],
			jmp[i][min(N - 1, j + (1 << i))]);
	}

	T query(int a, int b){
		if(b <= a) return inf;
		int on = 1, depth = 0;
		while(b - 2*on - 1 >= a) on *= 2, depth++;
		return min(jmp[depth][a], jmp[depth][b-on]);
	}
};
