/**
 * Date: 2014-11-28
 * Author: Johan Sannemo
 * Source: Folklore
 * Status: Tested on Kattis
 * Description: Calculate submatrix sums quickly, given upper-left and lower-right corners (half-open).
 * Usage:
 * SubMatrix<int> m(matrix);
 * m.sum(0, 0, 2, 2); // top left 4 elements
 * Time: O(N^2 + Q)
 */

template <class T>
struct SubMatrix {
	vector<vector<T>> p;
	SubMatrix(vector<vector<T>>& v) {
		int n = sz(v), m = sz(v[0]);
		p.assign(n+1, vector<T>(m+1));
		rep(i,0,n) rep(j,0,m) {
			p[i+1][j+1] = v[i][j] +
				p[i][j+1] + p[i+1][j] - p[i][j];
		}
	}
	T sum(int r1, int c1, int r2, int c2) {
		return p[r2][c2] - p[r2][c1] - p[r1][c2] + p[r1][c1];
	}
};
