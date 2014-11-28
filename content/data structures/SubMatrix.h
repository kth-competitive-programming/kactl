/**
 * Date: 2014-11-28
 * Author: Johan Sannemo
 * Source: Folklore
 * Description: Calculate submatrix sums quickly, given upper-left and lower-right corners (inclusive).
 * Time: O(n^2 + q)
 */

template<typename T>
struct SubMatrix {
	int n, m;
	vector<vector<T>> p;
	SubMatrix(vector<vector<T>>& v){
		n = v.size(), m = v[0].size();
		p.assign(n, vector<T>(m, 0));
		rep(i,0,n){
			rep(j,0,m){
				p[i][j] += v[i][j];
				if(i) p[i][j] += p[i-1][j];
				if(j) p[i][j] += p[i][j-1];
				if(i&&j) p[i][j] -= p[i-1][j-1];
			}
		}
	}

	T sum(int r1, int c1, int r2, int c2){
		T ans = 0;
		ans += p[r2][c2];
		if(c1) ans -= p[r2][c1-1];
		if(r1) ans -= p[r1-1][c2];
		if(r1&&c1) ans += p[r1-1][c1-1];
		return ans;
	}
};
