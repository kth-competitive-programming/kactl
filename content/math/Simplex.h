/**
 * Author:
 * Description: 
 * Usage: 
 * Time: 
 */
#pragma once

using T = long double;
const int N = 410, M = 30010;
const T eps = 1e-7;
int n, m;
int Left[M], Down[N];
// time complexity: exponential. fast $O(MN^2)$ in experiment. dependent on the modeling.
// Ax <= b, max c^T x. 최댓값: v, 답 추적: sol[i]. 1 based
T a[M][N], b[M], c[N], v, sol[N];
bool eq(T a, T b) { return fabs(a - b) < eps;  }
bool ls(T a, T b) { return a < b && !eq(a, b); }
void init(int p, int q) {
	n = p; m = q; v = 0;
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++) a[i][j]=0;
	}
	for(int i = 1; i <= m; i++) b[i]=0;
	for(int i = 1; i <= n; i++) c[i]=sol[i]=0;
}
void pivot(int x,int y) {
	swap(Left[x], Down[y]);
	T k = a[x][y]; a[x][y] = 1;
	vector<int> nz;
	for(int i = 1; i <= n; i++){
		a[x][i] /= k;
		if(!eq(a[x][i], 0)) nz.push_back(i);
	}
	b[x] /= k;

	for(int i = 1; i <= m; i++){
		if(i == x || eq(a[i][y], 0)) continue;
		k = a[i][y]; a[i][y] = 0;
		b[i] -= k*b[x];
		for(int j : nz) a[i][j] -= k*a[x][j];
	}
	if(eq(c[y], 0)) return;
	k = c[y]; c[y] = 0;
	v += k*b[x];
	for(int i : nz) c[i] -= k*a[x][i];
}
// 0: found solution, 1: no feasible solution, 2: unbounded
int solve() {
	for(int i = 1; i <= n; i++) Down[i] = i;
	for(int i = 1; i <= m; i++) Left[i] = n+i;
	while(1) { // Eliminating negative b[i]
		int x = 0, y = 0;
		for(int i = 1; i <= m; i++) if (ls(b[i], 0) && (x == 0 || b[i] < b[x])) x = i;
		if(x == 0) break;
		for(int i = 1; i <= n; i++) if (ls(a[x][i], 0) && (y == 0 || a[x][i] < a[x][y])) y = i;
		if(y == 0) return 1;
		pivot(x, y);
	}
	while(1) {
		int x = 0, y = 0;
		for(int i = 1; i <= n; i++)
			if (ls(0, c[i]) && (!y || c[i] > c[y])) y = i;
		if(y == 0) break;
		for(int i = 1; i <= m; i++)
			if (ls(0, a[i][y]) && (!x || b[i]/a[i][y] < b[x]/a[x][y])) x = i;
		if(x == 0) return 2;
		pivot(x, y);
	}
	for(int i = 1; i <= m; i++) if(Left[i] <= n) sol[Left[i]] = b[i];
	return 0;
}