/**
* Description: Matrix tree theorem
* Author: github
* Source: github
* Date: today
*/
// This code is checked by problem spoj104
// Matrix tree theorem for calculating the number of spanning trees of a general graph
// For more detail, please view:
// http://www.spoj.pl/problems/HIGH/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 32
typedef long long LL;
int n, m;
LL ma[N][N], a[N][N];

//determinant calculation: euclid extension
void det(int v)
{
	int i, j, k;
	LL ans = 1, t;
	for (i = 0; i < v; i++){
		for (j = i+1; j < v; j++){
			// euclid
			while (a[j][i] != 0){
				t = a[i][i] / a[j][i];
				for (k = i; k < v; k++){
					a[i][k] = (a[i][k] - a[j][k] * t);
				}
				for (k = 0; k < v; k++) 
					swap(a[i][k], a[j][k]);
				ans = -ans;
			}
		}
		if (a[i][i] == 0){
			ans = 0;
			break;
		}
		ans = ans * a[i][i];
	}
	printf("%lld\n", ans);
}

int main()
{
	int ca, i, u, v;
	scanf("%d", &ca);
	while (ca--){
		memset(ma, 0, sizeof(ma));
		scanf("%d%d", &n, &m);
		for (i = 0; i < m; i++){
			scanf("%d%d", &u, &v);
			u--, v--;
			ma[u][u]++;
			ma[v][v]++;
			ma[u][v]--;
			ma[v][u]--;
		}
		memset(a, 0, sizeof(a));
		for (u = 1; u < n; u++)
			for (v = 1; v < n; v++)
				a[u-1][v-1] = ma[u][v];
		det(n-1);
	}
}

