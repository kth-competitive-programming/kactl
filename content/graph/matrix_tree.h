/**
* Description: Matrix tree theorem
* Author: Unknown
* Source: Unknown
* Date: 2014-11-27
*/

//determinant calculation: euclid extension
ll det(vector<vi>& a) {
	ll ans = 1, t;
	rep(i,0,a.size()){
		rep(j,i+1,a.size()){
			while (a[j][i] != 0){
				t = a[i][i] / a[j][i];
				rep(k,i,v)
					a[i][k] = (a[i][k] - a[j][k] * t);
				}
				rep(k,0,a.size())
					swap(a[i][k], a[j][k]);
				ans = -ans;
			}
		}
		if (!a[i][i]){
			return 0;
		}
		ans *= a[i][i];
	}
	return ans;
}

void addEdge(vector<vi>& mat, int a, int b){
	mat[a][a]++; mat[b][b]++;
	mat[a][b]--; mat[b][a]--;
}

vector<vi> reduce(vector<vi>& mat){
	vector<vi> reduced(mat.size() - 1, vi(mat.size()-1));
	rep(i,1,mat.size()) rep(j,1,mat.size())
		reduced[i-1][j-1] = mat[i][j];
	return mat;
}
