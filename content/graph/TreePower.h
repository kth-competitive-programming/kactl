/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * Source: Folklore
 * Status: Tested at Petrozavodsk
 * Description: Calculate power of two jumps in a tree.
 * Assumes the root node points to itself.
 * Time: $O(|V| \log |V|)$
 */

vector<vi> treeJump(vi& P){
	int on = 1, d = 1;
	while(on < (int)P.size()) on *= 2, d++;
	vector<vi> jmp(d, vi(P.size()));
	jmp[0] = P;
	rep(i,1,d) rep(j,0,P.size())
		jmp[i][j] = jmp[i-1][jmp[i-1][j]];
	return jmp;
}

int jmp(vector<vi>& tbl, int nod, int steps){
	rep(i,0,tbl.size())
		if(steps&(1<<i)) nod = tbl[i][nod];
	return nod;
}
