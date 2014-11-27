/**
* Description: RMQ structure
* Author: github
* Source: github
* Date: today
*/
// Weighted perfect match, KM algorithm
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1024
#define INF 1000000000
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int w, s, nx, ny;
int cost[N][N], cx[N], cy[N], lx[N], ly[N];
int vx[N], vy[N];

int path(int u){
	vx[u] = 1;
	int v;
	for (v = 0; v < ny; v++){
		if (cost[u][v] == lx[u] + ly[v] && !vy[v]){
			vy[v] = 1;
			if (cy[v] == -1 || path(cy[v])){
				cx[u] = v;
				cy[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

void km(){
	int i, j, k, l, dif, ans = 0;
	memset(cx, -1, sizeof(cx));
	memset(cy, -1, sizeof(cy));
	memset(ly, 0, sizeof(ly));
	for (i = 0; i < nx; i++) lx[i] = -INF;
	for (i = 0; i < nx; i++){
		for (j = 0; j < ny; j++){
			lx[i] = MAX(lx[i], cost[i][j]);
		}
	}
	for (i = 0; i < nx; i++){
		if (cx[i] == -1){
			memset(vx, 0, sizeof(vx));
			memset(vy, 0, sizeof(vy));

			while (!path(i)){
				//cout << "I " << i << endl;
				dif = INF;
				for (j = 0; j < nx; j++){
					if (!vx[j]) continue;
					for (k = 0; k < ny; k++){
						if (vy[k]) continue;
						dif  = MIN(dif, lx[j] + ly[k] - cost[j][k]);
					}
				}
				for (j = 0; j < nx; j++){
					if (vx[j]){
						lx[j] -= dif;
						vx[j] = 0;
					}
				}
				for (j = 0; j < ny; j++){
					if (vy[j]){
						ly[j] += dif;
						vy[j] = 0;
					}
				}
			}
		}
	}
	for (i = 0; i < nx; i++){
		ans += cost[i][cx[i]];
	}
	cout << ans << endl;
}

int main(){
	while (cin >> w >> s){
		memset(cost, 0, sizeof(cost));
		for (int i = 0; i < w; i++){
			for (int j = 0 ; j < s; j++){
				cin >> cost[i][j];
			}
		}
		nx = MAX(w, s);
		ny = MAX(w, s);
		km();
	}
}

