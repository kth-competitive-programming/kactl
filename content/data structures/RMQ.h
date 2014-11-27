/**
* Description: RMQ structure. Queries are exclusive!
* Date: 2014-11-27
* Source: folklore
* Author: Johan Sannemo
* Time: O(N \log N + Q)
*/

struct RMQ {
	vector<vi> h;
	RMQ(vi val){
		int l = 1, j = 1;
		while(l*2 <= val.size()) j++, l <<= 1;
		h.assign(val.size(), vi(j));
		rep(i,0,val.size()) jumps[i][0] = val[i];
		for(j = l = 1; l*2 <= val.size(); j++, l <<= 1)
			rep(i,0,val.size())
				h[i][j] = min(h[i][j-1], h[i+l][j-1]);
	}
	int query(int start, int end){
		int j = 0, l = 1;
		while(2*l < end - start) j++, l<<=1;
		return min(h[start][j], h[end-l][j]);
	}
};
